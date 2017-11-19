import PhylloxeraPy

from ROOT import Phylloxera, Base
import ROOT
from ROOT import RooRealVar, RooArgSet, RooDataSet
KE = ROOT.RooRealVar("KE", "KE", 17500, 17000, 18000)
mean = ROOT.RooRealVar("mean", "mean", 17800)
width = ROOT.RooRealVar("width", "width", 1)

b = Phylloxera.KryptonLine("KrLine", "KrLine", KE, mean, width)
print(b)
test = Phylloxera.PdfFactory()
print(test)
test.GetSmearedPdf("testing", TObjectNew.Gaussian, KE, b, width)
