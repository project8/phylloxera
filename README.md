# Phylloxera

A library of RooFit classes and functions for analyzing Krypton and Tritium Spectra

## Requirements

## Quick Setup

- Clone Github repository and update submodule:
```bash
git clone "https://github.com/project8/phylloxera"
cd phylloxera
git submodule update --init --recursive
```
- Install: 
```bash
mkdir build
cd build
cmake ..
make -j install
```
- Update your PYTHONPATH: in your ~/.bash_profile add 
```bash
export PYTHONPATH=/path/to/phylloxera/build:${PYTHONPATH}
```

## Python Interface

In your Python script, you will need to import PhylloxeraPy using
```python
import PhylloxeraPy
PhylloxeraPy.loadLibraries(True)
```
From there, you can access the classes defined in Phylloxera via ROOT. Ex: 
```python
from ROOT import KryptonLine, RooRealVar, RooArgSet, TCanvas
KE = RooRealVar("KE", "KE", 30490, 30470, 30500)
meanKrLine = RooRealVar("meanKrLine", "meanKrLine", 30490, 30470, 30500)
widthKrLine = RooRealVar("width", "width", 1, 0.01, 10)
KrLine = KryptonLine("KrLine", "KrLine", KE, meanKrLine, widthKrLine)

data = KrLine.generate(RooArgSet(KE), 1000)
KrLine.fitTo(data)

c1 = TCanvas("c1", "c1", 600, 400)
KEframe = KE.frame()
data.plotOn(KEframe)
KrLine.plotOn(KEframe)
KEframe.Draw()
c1.SaveAs("dataPlotFit.pdf")
```