#include "TH1F.h"
#include "TCanvas.h"
#include "TMath.h"

#include "VectorTools.cpp"
#include "TritiumSpectrum.cpp"

// void DrawKuriePlot(TH1F* hist){
//     auto axis = hist->GetXaxis();
//     auto kurieHisto = new TH1F("kurieHisto","Kurie plot",hist->GetNbinsX(),axis->GetXmin(),axis->GetXmax());
//     for (int iBin=0; iBin<hist->GetNbinsX(); iBin++){
//         double kurieValue = TMath::Sqrt(hist->GetBinContent(iBin)/RFactor(hist->GetBinCenter(iBin),1));
//         kurieHisto->SetBinContent(iBin,kurieValue);
//     }
//     TCanvas canKuriePlot("canKuriePlot","canKuriePlot",600,400);
//     canKuriePlot.Draw();
//     kurieHisto->Draw("Hist");
//     // canKuriePlot.SaveAs("kurieplot.pdf");
//     return kurieHisto;
// }

TH1F getKuriePlot(std::vector<double> vData){
    double xMin = getMinFromVector(vData);
    double xMax = getMaxFromVector(vData);
    TH1F histo("data","data",100,xMin,xMax);
    TH1F kurieHisto("kurieHisto","kurieHisto",100,xMin,xMax);
    for (int i=0; i<vData.size(); ++i){
        histo.Fill(vData[i]);
    }
    for (int iBin=0; iBin<histo.GetNbinsX(); iBin++){
        double kurieValue = TMath::Sqrt(histo.GetBinContent(iBin)/RFactor(histo.GetBinCenter(iBin),1));
        kurieHisto.SetBinContent(iBin,kurieValue);
    }
    return kurieHisto;
    }