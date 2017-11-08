
import os
from ROOT import ROOT, gInterpreter, gSystem

print("Include headers")
path = os.path.join(os.path.dirname(
    os.path.abspath(__file__)), "build/include/Phylloxera")
for afile in os.listdir(path):
    if afile.endswith(".hh"):
        print(os.path.join(path, afile))
        gInterpreter.ProcessLine(
            '#include "{}"'.format(os.path.join(path, afile)))

print("Import lib")
path = os.path.join(os.path.dirname(
    os.path.abspath(__file__)), "build/lib")
for afile in os.listdir(path):
    if afile.endswith(".dylib"):
        print(afile)
        gSystem.Load(afile)
