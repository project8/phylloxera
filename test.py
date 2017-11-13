import PhylloxeraPy

# a = PhylloxeraPy.PhylloxeraInterface()
from ROOT import KryptonLine, PdfFactory, RooGaussian, RooPlot, TObject
import ROOT
from ROOT import RooRealVar, RooArgSet, RooDataSet
KE = ROOT.RooRealVar("KE", "KE", 17500, 17000, 18000)
mean = ROOT.RooRealVar("mean", "mean", 17800)
width = ROOT.RooRealVar("width", "width", 1)

b = KryptonLine("KrLine", "KrLine", KE, mean, width)
factory = PdfFactory()
obj = factory.createInstance(int)(1)
print(obj)


gaus = factory.createInstance[RooGaussian]()

gauss = RooGaussian("gauss", "gauss", KE, mean, width)
data = b.generate(RooArgSet(KE), 1000)

print(data)

can = ROOT.TCanvas("can", "can", 600, 400)
frame = KE.frame()

data.plotOn(frame)
frame.Draw()
can.SaveAs("test.pdf")


import inspect
print(inspect.getmembers(PdfFactory, lambda a: not(inspect.isroutine(a))))

# factory.createData[KryptonLine](b, KE, 1000)

# import inspect
# print(inspect.getmembers(KryptonLine, lambda a: not(inspect.isroutine(a))))
# print(b.evaluate())

# data = b.generate(RooArgSet(KE), int(1000))


# print(a)
# print(a.getDouble())

# # from Phylloxera import PdfFactory

# KE = RooRealVar("KE", "kineticEnergy", -10., 10.)
# mass = RooRealVar("mass", "Reconstructed Candidate Mass", 0.0, 8.0, "GeV")
# a = Phylloxera.RooKrTest("KryptonTest", "KryptonTest", KE)


# from ROOT import RooArgSet
# data = a.generate(RooArgSet(KE), 1000)
# # data.Print()

# b = RooKryptonLine()
# print(a)
# print(b)

# RooMsgService.instance().setSilentMode(True)

# a = Phylloxera.PdfFactory()


# import KatydidPy
