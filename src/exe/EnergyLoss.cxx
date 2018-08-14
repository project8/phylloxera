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
#include "RooFitResult.h"


#include "RealTritiumSpectrum.hh"
#include "AsymmetricKryptonLine.hh"
#include "KryptonLine.hh"
// #include "SmearedTritiumSpectrum.hh"
#include "Plots.cpp"
#include "RooFitTools.cpp"

#include "RooRealVar.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"

#include "EnergyLossPdf.hh"
#include "KryptonLine.hh"
#include "PdfFactory.hh"

#include <iostream>

int main()
{

    double KrMean = 178000;
    double proba = 0.3;

    // Using parameters from Aseev, Eur. Phys. J. D 10, 39–52 (2000)

    RooRealVar KE("KE", "KE", KrMean + 0, KrMean + 100);
    KE.setRange("KryptonLine", 16900, 17100);
    KE.setRange("EnergyLoss", 0, 50);
    RooRealVar mean1("mean1", "mean1", 12.6);
    RooRealVar mean2("mean2", "mean2", 14.3);
    RooRealVar width1("width1", "width1", 1.85);
    RooRealVar width2("width2", "width2", 12.5);
    RooRealVar amplitude1("amplitude1", "amplitude1", 10);
    RooRealVar amplitude2("amplitude2", "amplitude2", 45);

    RooRealVar meanKr("meanKr", "meanKr", 20 + KrMean, KrMean, KrMean + 30);
    RooRealVar HWHMKr("widthKr", "widthKr", 2);

    RooRealVar One("one", "one", 1);
    RooRealVar Proba("proba", "proba", proba);
    RooRealVar ProbaSquare("proba2", "proba2", TMath::Power(proba, 2));
    RooRealVar ProbaThree("proba3", "proba3", TMath::Power(proba, 3));
    RooRealVar ProbaFour("proba4", "proba4", TMath::Power(proba, 4));

    PdfFactory *factory = new PdfFactory("myFactory");

    EnergyLossPdf *energyLossPdf = new EnergyLossPdf("energyLoss", "Energy Loss pdf", KE, mean1, mean2, width1, width2, amplitude1, amplitude2);
    RooFFTConvPdf *OneConvPdf = factory->GetSelfConvolPdf<EnergyLossPdf>("OneConvPdf", &KE, energyLossPdf);
    RooFFTConvPdf *TwoConvPdf = factory->GetMultiSelfConvolPdf<EnergyLossPdf>("TwoConvPdf", &KE, energyLossPdf, 2);
    RooFFTConvPdf *FourConvPdf = factory->GetMultiSelfConvolPdf<EnergyLossPdf>("FourConvPdf", &KE, energyLossPdf, 4);

    KryptonLine *KrLineshape = new KryptonLine("KrLineShape", "Krypton lineshape", KE, meanKr, HWHMKr);
    RooFFTConvPdf *distortedKrLineshape1 = factory->GetMultiConvolPdf("distKrLineshape", &KE, KrLineshape, energyLossPdf, 1, 1000000);
    RooFFTConvPdf *distortedKrLineshape2 = factory->GetMultiConvolPdf("distortedKrLineshape2", &KE, KrLineshape, energyLossPdf, 2, 1000000);
    RooFFTConvPdf *distortedKrLineshape3 = factory->GetMultiConvolPdf("distortedKrLineshape3", &KE, KrLineshape, energyLossPdf, 3, 1000000);
    RooFFTConvPdf *distortedKrLineshape4 = factory->GetMultiConvolPdf("distortedKrLineshape4", &KE, KrLineshape, energyLossPdf, 4, 1000000);

    RooAddPdf *addPdfs = new RooAddPdf("addPdfs", "addPdfs", RooArgList(*KrLineshape, *distortedKrLineshape1, *distortedKrLineshape2, *distortedKrLineshape3, *distortedKrLineshape4), RooArgList(One, Proba, ProbaSquare, ProbaThree, ProbaFour));
    RooDataSet *data = addPdfs->generate(KE, 10000);
    RooFitResult* r = addPdfs->fitTo(*data,RooFit::Save());
    addPdfs->Print("v");
    r->Print();

    RooPlot *frame = KE.frame(0, 100);
    energyLossPdf->plotOn(frame);
    OneConvPdf->plotOn(frame);
    TwoConvPdf->plotOn(frame);
    FourConvPdf->plotOn(frame);
    // Draw plot on canvas
    auto can = new TCanvas("can", "Energy loss pdfs", 600, 400);
    gPad->SetLeftMargin(0.15);
    frame->GetYaxis()->SetTitleOffset(1.6);
    frame->Draw();
    can->Draw();
    can->SaveAs("EnergyLossPdfs.pdf");

    RooPlot *frame2 = KE.frame(0 + KrMean, 100 + KrMean);
    data->plotOn(frame2);
    addPdfs->plotOn(frame2);
    KrLineshape->plotOn(frame2, RooFit::LineColor(kRed));
    distortedKrLineshape1->plotOn(frame2, RooFit::LineColor(kRed));
    distortedKrLineshape2->plotOn(frame2, RooFit::LineColor(kRed));
    distortedKrLineshape3->plotOn(frame2, RooFit::LineColor(kRed));
    distortedKrLineshape4->plotOn(frame2, RooFit::LineColor(kRed));
    auto can2 = new TCanvas("data", "data", 600, 400);
    gPad->SetLeftMargin(0.15);
    frame2->GetYaxis()->SetTitleOffset(1.6);
    frame2->Draw();
    can2->Draw();
    can2->SaveAs("KryponeLineshapes.pdf");

    // addPdfs->plotOn(frame2,RooFit::Range("KryptonLine"));
    // // Draw data on canvas

    return 0;
}