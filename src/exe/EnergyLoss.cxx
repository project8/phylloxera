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
#include "MultiEnergyLossesPdf.hh"
#include "PdfFactory.hh"

#include <iostream>

int main()
{

    // Using parameters from Aseev, Eur. Phys. J. D 10, 39–52 (2000)


    RooRealVar KE("KE", "KE", 0, 50);
    RooRealVar mean1("mean1", "mean1", 12.6, 8, 15);
    RooRealVar mean2("mean2", "mean2", 14.3);
    RooRealVar width1("width1", "width1", 1.85);
    RooRealVar width2("width2", "width2", 12.5);
    RooRealVar amplitude1("amplitude1", "amplitude1", 10);
    RooRealVar amplitude2("amplitude2", "amplitude2", 15);

    RooRealVar One("one", "one", 1);
    RooRealVar Proba("proba", "proba", 0.3);
    RooRealVar ProbaSquare("proba", "proba", 0.09);

    PdfFactory *factory = new PdfFactory("myFactory");

    EnergyLossPdf *energyLossPdf = new EnergyLossPdf("energyLoss", "Energy Loss pdf", KE, mean1, mean2, width1, width2, amplitude1, amplitude2);
    RooFFTConvPdf *oneConvPdf = factory->GetSelfConvolPdf<EnergyLossPdf>("selfConvolvedTestPdflaskfasd", &KE, energyLossPdf);
    RooFFTConvPdf *TwoConvPdf = factory->GetMultiSelfConvolPdf<EnergyLossPdf>("selfConvolvedTestPdf", &KE, energyLossPdf, 2);
    RooAddPdf *addPdfs = new RooAddPdf("addPdfs", "addPdfs", RooArgList(*energyLossPdf, *oneConvPdf, *TwoConvPdf), RooArgList(One, Proba, ProbaSquare));

    RooDataSet* data = addPdfs->generate(KE,5000) ;

    RooPlot *frame = KE.frame(RooFit::Title("pdfs"));
    energyLossPdf->plotOn(frame);
    oneConvPdf->plotOn(frame);
    TwoConvPdf->plotOn(frame);
    addPdfs->plotOn(frame, RooFit::LineColor(kRed));
    // Draw plot on canvas
    auto can = new TCanvas("pdfs", "pdfs", 600, 400);
    gPad->SetLeftMargin(0.15);
    frame->GetYaxis()->SetTitleOffset(1.6);
    frame->Draw();
    can->Draw();
    can->SaveAs("Pdfs.pdf");

    RooPlot* frame2 = KE.frame(RooFit::Title("Data and fit")) ;
    data->plotOn(frame2) ;
    addPdfs->fitTo(*data) ;
    addPdfs->plotOn(frame2) ;
    // Draw data on canvas
    auto can2 = new TCanvas("data", "data", 600, 400);
    gPad->SetLeftMargin(0.15);
    frame2->GetYaxis()->SetTitleOffset(1.6);
    frame2->Draw();
    can2->Draw();
    can2->SaveAs("dataFit.pdf");


    return 0;
}