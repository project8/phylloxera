#include "TF1.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "TStyle.h"
#include "TFitResultPtr.h"
#include "RooGaussian.h"
#include "RooFFTConvPdf.h"
#include "RooNumConvPdf.h"
#include "RooAddPdf.h"
#include "RooUniform.h"
#include "RooDataHist.h"
#include "RooGenericPdf.h"

#include "RealTritiumSpectrum.hh"
// #include "SmearedTritiumSpectrum.hh"
#include "Plots.cpp"
#include "RooFitTools.cpp"

// #include "logger.hh"

namespace Phylloxera
{
const double Q = 18.6E+3; // eV
// const double t = 1 * seconds_per_year();
const double massNu = 0;
const double background = 1E-6;

const double Emin = Q - 1000.;
const double Emax = Q + 1000;
const double KE_conv_min = Emin - 4;
const double KE_conv_max = Emax + 4;

// LOGGER(kp, "KuriePlot");

void spectrum()
{
    double KEmin = KE_conv_min;
    double KEmax = KE_conv_max;
    RooRealVar tKE("kineticEnergy", "Kinetic Energy", 18.5e3, KEmin, KEmax);

    // Tritium data
    RooRealVar tEndpoint("endpoint", "Endpoint", 18.6e3, 17e3, 19e3);
    RooRealVar tNeutrinoMass("neutrinoMass", "NeutrinoMass", 100., 0., 1000.);
    RooRealVar tB("background", "Background", 0.);
    RealTritiumSpectrum tritumSpectrum("tritiumSpectrum", "TritiumSpectrum", tKE, tEndpoint, tNeutrinoMass);

    //Background data
    RooDataSet *dataTritium = tritumSpectrum.generate(tKE, 100000);
    RooUniform background("background", "Background", tKE);
    RooDataSet *databackground = background.generate(tKE, 1000);

    // Addig data
    std::vector<double> vData = getDataFromDataset(dataTritium, "kineticEnergy");
    std::vector<double> vBackground = getDataFromDataset(databackground, "kineticEnergy");
    for (int iVector = 0; iVector < vBackground.size(); ++iVector)
    {
        vData.push_back(vBackground[iVector]);
    }

    // Fit
    TH1F kurieHisto = getKuriePlot(vData);
    auto axis = kurieHisto.GetXaxis();
    // The function below is definitely not the right one.
    // Need to calculate from the tritium model what the right shape is.
    TF1 *kuriefit = new TF1("kuriefit", "[0]*([1]-x)*(x<[1]-[2])+[3]", axis->GetXmin(), axis->GetXmax());
    // [0]: slope
    // [1]: endpoint value
    // [2]: neutrino mass
    // [3]: background
    //
    kuriefit->SetParLimits(0, 1e-8, 1e-6);
    kuriefit->SetParLimits(1, 18000, 19000);
    kuriefit->SetParameter(0, 1.5e-8);
    kuriefit->FixParameter(1, 18600.);
    kuriefit->SetParameter(2, 10.);

    gStyle->SetOptFit(1011);
    TFitResultPtr r = kurieHisto.Fit(kuriefit, "MQLE");
    double chi2 = kuriefit->GetChisquare();
    double ndf = kuriefit->GetNDF();
    double p0 = kuriefit->GetParameter(0);
    double e0 = kuriefit->GetParError(0);
    double p1 = kuriefit->GetParameter(1);
    double e1 = kuriefit->GetParError(1);

    double rescaled_e0 = e0 * TMath::Sqrt(chi2 / ndf);
    double rescaled_e1 = e1 * TMath::Sqrt(chi2 / ndf);

    // LINFO(kp, "Fit results:\n"
    //               << "chi2 / ndf = " << chi2 << "/" << ndf << "\n"
    //               << "par[0]= " << p0 << "+-" << rescaled_e0 << "\n"
    //               << "par[1]= " << p1 << "+-" << rescaled_e1);

    // Second round fit
    for (int iBin = 0; iBin < kurieHisto.GetNbinsX(); ++iBin)
    {
        kurieHisto.SetBinError(iBin, kurieHisto.GetBinError(iBin) * sqrt(chi2 / ndf));
    }
    TFitResultPtr r_2 = kurieHisto.Fit(kuriefit, "MQLE");
    double chi2_2 = kuriefit->GetChisquare();
    double ndf_2 = kuriefit->GetNDF();
    double p0_2 = kuriefit->GetParameter(0);
    double e0_2 = kuriefit->GetParError(0);
    double p1_2 = kuriefit->GetParameter(1);
    double e1_2 = kuriefit->GetParError(1);

    double rescaled_e0_2 = e0_2 * TMath::Sqrt(chi2 / ndf);
    double rescaled_e1_2 = e1_2 * TMath::Sqrt(chi2 / ndf);

    // LINFO(kp, "Fit results:\n"
    //               << "Fit results after second round:"
    //               << "\n"
    //               << "chi2 / ndf = " << chi2_2 << "/" << ndf_2 << "\n"
    //               << "par[0]= " << p0_2 << "+-" << rescaled_e0_2 << "\n"
    //               << "par[1]= " << p1_2 << "+-" << rescaled_e1_2);

    // Plotting
    TCanvas *c = new TCanvas("rf103_interprfuncs", "rf103_interprfuncs", 600, 400);
    kurieHisto.Draw("hist");
    kurieHisto.GetXaxis()->SetRangeUser(axis->GetXmin() * 0.9, axis->GetXmax() * 1.1);
    kuriefit->Draw("same");
    c->SaveAs("kurieplot.pdf");

    RooPlot *xframe2 = tKE.frame(RooFit::Title("Spectrum and background"));
    databackground->plotOn(xframe2);
    background.plotOn(xframe2);
    dataTritium->plotOn(xframe2);
    tritumSpectrum.plotOn(xframe2);

    // // Draw all frames on a canvas
    gPad->SetLeftMargin(0.15);
    xframe2->GetYaxis()->SetTitleOffset(1.4);
    xframe2->Draw();
    c->SetLogy();
    c->SaveAs("spectrumBackground.pdf");
}

void smeared_spectrum()
{
    double KEmin = KE_conv_min;
    double KEmax = KE_conv_max;
    RooRealVar tEndpoint("endpoint", "Endpoint", 18.6e3, KEmin, KEmax);
    RooRealVar tNeutrinoMass("neutrinoMass", "NeutrinoMass", 0., 0., 1000.);
    RooRealVar tKE("KE", "Kinetic Energy", KEmin, KEmax);
    RooRealVar tB("background", "Background", 0.0001);

    RooRealVar tWidth("width", "Width", 0.1);
    RooRealVar tMean("mean", "Mean", 0.);
    // RooGaussian gaussian("gaussian","gaussian",tKE,tMean,tWidth);

    RooRealVar mg("mg", "mg", 0);            // mean of the gaussian for the convolution
    RooRealVar sg("sg", "sg", 0.1, 0., 10.); //width of the convolution
    // RooRealVar meansg("meansg","meansg",sigmaKE); //mean value of the width
    // RooRealVar errorsg("errorsg","errorsg",sigmaKE*relErrSigmaKE); // error on the width of the convolution

    RooGaussian gauss("gauss", "gauss", tKE, mg, sg);
    RealTritiumSpectrum simpleSpectrum("tritiumSpectrum", "TritiumSpectrum", tKE, tEndpoint, tNeutrinoMass);
    RooGenericPdf beta("beta", "background+ (endpoint-KE>neutrinoMass)*3*1e10/13/pow(endpoint,3)*(endpoint-KE)*sqrt(pow(endpoint-KE,2)-pow(neutrinoMass,2))", RooArgSet(tKE, tEndpoint, tNeutrinoMass, tB));

    // RooRealVar signalfrac("signalfrac","fraction of component 1 in signal",1.) ;
    // RooAddPdf completeSpectrum("sig","Signal",RooArgList(beta,bkg),signalfrac) ;
    tKE.setBins(30000, "cache");

    RooFFTConvPdf smearedSpectrum("smearedSpectrum", "smearedSpectrum", tKE, beta, gauss);

    // RooSmearedTritiumSpectrum smearedTritumSpectrum("tritiumSpectrum", "TritiumSpectrum",tKE,tEndpoint,tNeutrinoMass,tWidth,RooSmearedTritiumSpectrum::Gaussian);

    // std::cout << "here" << std::endl;
    RooDataSet *dataSpectrum = smearedSpectrum.generate(tKE, 100000);
    // std::cout << "here" << std::endl;
    RooPlot *xframe2 = tKE.frame(RooFit::Title("Tailored Gaussian pdf"));
    dataSpectrum->plotOn(xframe2);
    // completeSpectrum.plotOn(xframe2) ;
    smearedSpectrum.plotOn(xframe2);

    // RooPlot* xframe3 = tKE.frame(RooFit::Title("Tailored  pdf")) ;
    // gaussian.plotOn(xframe3) ;

    TCanvas *c = new TCanvas("rf103_interprfuncs", "rf103_interprfuncs", 600, 400);
    c->SetLogy();
    gPad->SetLeftMargin(0.15);
    xframe2->GetYaxis()->SetTitleOffset(1.4);
    xframe2->Draw();
    // TH1F kurieHisto = getKuriePlot(getDataFromDataset(data2,"kineticEnergy"));
    c->SaveAs("testSmeared.pdf");

    // TCanvas* c2 = new TCanvas("rf103_interprfuncs","rf103_interprfuncs",600,400) ;
    // c2->SetLogy();
    // gPad->SetLeftMargin(0.15) ; xframe3->GetYaxis()->SetTitleOffset(1.4) ; xframe3->Draw() ;
    // TH1F kurieHisto = getKuriePlot(getDataFromDataset(data2,"kineticEnergy"));
    // c2->SaveAs("testSmeared2.pdf");
}

void makeAndUseModel()
{
    std::cout << "           ------------------------------------\n\
              Construct and use model and the data\n\
              ------------------------------------"
              << std::endl;

    // Construct observable
    // RooRealVar KE("KE","KE",KE_conv_min,KE_conv_max) ;
    ///////
    double KEmin = KE_conv_min;
    double KEmax = KE_conv_max;
    RooRealVar KE("KE", "KE", KEmin, KEmax);
    //////

    RooRealVar dt("dt", "dt", 10);
    RooRealVar tau("tau", "tau", 13);
    RooRealVar m_nu("m_nu", "m_nu", 0.001, -10, 10);
    // RooRealVar endpoint("endpoint","endpoint",Q,Q-1,Q+1) ;
    // RooRealVar Natoms("Natoms","Natoms",N_atoms,0.999*N_atoms,1.001*N_atoms) ;
    // RooRealVar b("b","b",background,0,10*background) ;

    //Fixing param of fit
    RooRealVar endpoint("endpoint", "endpoint", 18.6e3);
    RooRealVar b("b", "b", 1e-6);
    RooRealVar Natoms("Natoms", "Natoms", 10000);

    // Create beta spectrum pdf
    RooGenericPdf beta("beta", "b*dt + (endpoint-KE>m_nu)*3*Natoms*dt/tau/pow(endpoint,3)*(endpoint-KE)*sqrt(pow(endpoint-KE,2)-pow(m_nu,2))", RooArgSet(KE, endpoint, m_nu, dt, tau, Natoms, b));

    RooRealVar mg("mg", "mg", 0);            // mean of the gaussian for the convolution
    RooRealVar sg("sg", "sg", 0.1, 0., 10.); //width of the convolution
    // RooRealVar meansg("meansg","meansg",sigmaKE); //mean value of the width
    // RooRealVar errorsg("errorsg","errorsg",sigmaKE*relErrSigmaKE); // error on the width of the convolution

    RooGaussian gauss("gauss", "gauss", KE, mg, sg);
    std::cout << "Setting external constrain on sigmaKE: " << 0.1 << "+/-" << 10 << std::endl;
    // RooGaussian gaussErr("gaussErr","gaussErr",sg,RooFit::RooConst(0.1),RooFit::RooConst(0.1*10)) ;

    KE.setBins(30000, "cache");
    // Construct landau (x) gauss
    RooFFTConvPdf smeared_beta("smeared_beta", "beta (X) gauss", KE, beta, gauss);
    KE.setBins(6000);

    // double N_electrons = N_atoms*TMath::Power((1-KE_conv_min/Q),3)*10/13()+background*t*(KE_conv_max-KE_conv_min) ;
    // std::cout << "Number electrons in range: " << N_electrons << std::endl ;
    RooDataHist *data = smeared_beta.generateBinned(KE, 10000);
    data->SetName("dataset");

    // Adding items to the workspace
    // w->import(gaussErr);
    // w->import(smeared_beta);
    // w->import(*data);

    RooPlot *xframe4 = KE.frame(RooFit::Title("Tailored  pdf"));
    smeared_beta.plotOn(xframe4);
    data->plotOn(xframe4);

    TCanvas *c = new TCanvas("fs", "sadfsa", 600, 400);
    c->SetLogy();
    gPad->SetLeftMargin(0.15);
    xframe4->GetYaxis()->SetTitleOffset(1.4);
    xframe4->Draw();
    // TH1F kurieHisto = getKuriePlot(getDataFromDataset(data2,"kineticEnergy"));
    c->SaveAs("testOldModel.pdf");
}
}

using namespace Phylloxera;
int main()
{
    TStyle *m_gStyle = new TStyle();
    m_gStyle->SetOptFit(0011);
    m_gStyle->SetOptStat(0);
    spectrum();
    smeared_spectrum();
    makeAndUseModel();
    return 0;
}
