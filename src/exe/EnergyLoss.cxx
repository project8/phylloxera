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
// #include "MultiEnergyLossesPdf.hh"

int main()
{

    RooRealVar KE("KE", "KE", 0, 20);
    RooRealVar mean1("mean1", "mean1", 10);
    RooRealVar mean2("mean2", "mean2", 13);
    RooRealVar epsilonc("epsilonc", "epsilonc", 12);
    RooRealVar width1("width1", "width1", 1.2);
    RooRealVar width2("width2", "width2", 2);
    RooRealVar amplitude1("amplitude1", "amplitude1", 15);
    RooRealVar amplitude2("amplitude2", "amplitude2", 15);

    // EnergyLossPdf sajdnfa();
    KryptonLine sajdnfa2("energyLoss", "Energy Loss pdf", KE, mean1, mean2);
    // KryptonLine2 sajdnfa3("energyLoss", "Energy Loss pdf", KE, mean1, mean2);
    // AsymmetricKryptonLine lksmfk("energyLoss", "Energy Loss pdf", KE, mean1, mean2, epsilonc);
    EnergyLossPdf* energyLossPdf = new EnergyLossPdf("energyLoss", "Energy Loss pdf", KE, mean1, mean2, width1, width2, amplitude1, amplitude2, epsilonc);
    // auto pdf = new MultiEnergyLossesPdf("multiLoss", "multiLoss", );
    RooPlot *frame = KE.frame(RooFit::Title("plot"));
    energyLossPdf->plotOn(frame);

    // Draw plot on canvas
    auto can = new TCanvas("plot", "plot", 600, 400);
    gPad->SetLeftMargin(0.15);
    frame->GetYaxis()->SetTitleOffset(1.6);
    frame->Draw();

    can->Draw();
    can->SaveAs("plot.pdf");

    return 0;
}