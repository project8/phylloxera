#include "PdfFactory.hh"
#include "KryptonLine.hh"
#include "RooFitTools.cpp"
#include "RootFileInterface.cxx"

#include "RooFit.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooFFTConvPdf.h"
#include "RooDataSet.h"
#include "RooGenericPdf.h"
#include "RooGaussian.h"

#include "TCanvas.h"
#include "TFile.h"
#include "TKey.h"

#include "logger.hh"

LOGGER(p1fitter, "Phase I Krypton line fitter");

namespace Phylloxera
{
}

int main()
{
  LINFO(p1fitter, "Hello there!")
  Phylloxera::PdfFactory factory();

  auto KE = new RooRealVar("KE", "kinetic Energy", 17900, 18100);
  KE->setBins(10000, "cache");

  auto mean = new RooRealVar("mean", "meanKE", 18000, 17950, 18050);
  auto width = new RooRealVar("width", "widthLine", 0.5, 0.01, 10);
  auto KryptonLine = new Phylloxera::KryptonLine("KryptonLine", "Line", *KE, *mean, *width);

  auto meanGauss = new RooRealVar("meanGauss", "meanGauss", 0);
  auto smearingWidth = new RooRealVar("smearingWidth", "smearingWidth", 3, 0.01, 10);
  auto gauss = new RooGaussian("gauss", "gauss", *KE, *meanGauss, *smearingWidth);
  // auto smearedLine = factory->GetSmearedPdf<Phylloxera::KryptonLine>("smearedLine", Phylloxera::PdfFactory::Gaussian, KE, KryptonLine, meanGauss, smearingWidth);

  // RooDataSet *data = smearedLine->generate(*KE, 1000);
  // smearedLine->fitTo(*data);
  // TCanvas *can = new TCanvas("can", "can", 600, 400);
  // RooPlot *xframe = KE->frame(RooFit::Title("Dataset"));
  // data->plotOn(xframe);
  // // smearedLine->plotOn(xframe, RooFit::LineColor(kBlue));
  // xframe->Draw();
  // can->SaveAs("test.pdf");

  // Phylloxera::RootFileInterface filereader("test.root", Phylloxera::RootFileInterface::FileOption::RECREATE);
  // TFile *file = filereader.GetTFile();
  // smearedLine->Write();
  // KryptonLine->Write();
  // // gDirectory->WriteObject(value, "test");
  // file->Write();
  // file->Close();

  // TFile f("test.root");
  // TIter next(f.GetListOfKeys());
  // TKey *key;
  // while ((key = (TKey *)next()))
  // {
  //   printf("key: %s points to an object of class: %s at %d\n",
  //          key->GetName(),
  //          key->GetClassName(),
  //          key->GetSeekKey());
  // }
  // Phylloxera::KryptonLine *outLine = (Phylloxera::KryptonLine *)f.Get("KryptonLine");
  // std::cout << outLine->analyticalIntegral(1) << std::endl;
  // f.Close();
}