#include "TH1F.h"
#include "TCanvas.h"
#include "TMath.h"

#include "VectorTools.cpp"
#include "TritiumSpectrum.cpp"

// namespace Phylloxera
// {

TH1F getKuriePlot(std::vector<double> vData)
{
    double xMin = getMinFromVector(vData);
    double xMax = getMaxFromVector(vData);
    TH1F histo("data", "data", 100, xMin, xMax);
    TH1F kurieHisto("kurieHisto", "kurieHisto", 100, xMin, xMax);
    for (int i = 0; i < vData.size(); ++i)
    {
        histo.Fill(vData[i]);
    }
    for (int iBin = 0; iBin < histo.GetNbinsX(); iBin++)
    {
        double kurieValue = TMath::Sqrt(histo.GetBinContent(iBin) / RFactor(histo.GetBinCenter(iBin), 1));
        kurieHisto.SetBinContent(iBin, kurieValue);
    }
    return kurieHisto;
}
// }
