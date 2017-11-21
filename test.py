import PhylloxeraPy

from ROOT import Phylloxera

import ROOT
from ROOT import RooRealVar, RooArgSet, RooDataSet
from ROOT.Phylloxera import PdfFactory
KE = ROOT.RooRealVar("KE", "KE", 17500, 17000, 18000)
mean = ROOT.RooRealVar("mean", "mean", 17800)
width = ROOT.RooRealVar("width", "width", 1)

b = Phylloxera.KryptonLine("KrLine", "KrLine", KE, mean, width)
data = b.generate(RooArgSet(KE), 1000)
print(data)
data.Print()

cdf = b.createCdf(ROOT.RooArgSet(KE))
c1 = ROOT.TCanvas("c1", "c1", 600, 400)
KEframe = KE.frame()
cdf.plotOn(KEframe)
KEframe.Draw()
c1.SaveAs("cdf.pdf")

b = Phylloxera.RealTritiumSpectrum()
test = PdfFactory()
print(test)
test.GetSmearedPdf("testing", TObjectNew.Gaussian, KE, b, width)
