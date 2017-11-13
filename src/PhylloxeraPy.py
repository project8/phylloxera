
import logging
import colorlog

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)
base_format = '%(asctime)s{}[%(levelname)-8s] %(name)s(%(lineno)d) -> {}%(message)s'
formatter = colorlog.ColoredFormatter(
    base_format.format('%(log_color)s', '%(purple)s'),
    datefmt='%Y-%m-%dT%H:%M:%SZ'[:-1],
    reset=True,
)
handler = logging.StreamHandler()
handler.setFormatter(formatter)
logger.addHandler(handler)


def print_logo():
    print('\n\
       ` .` :--..`       ...-:-`:.\n\
      .-++: ``..//:--:/:-..   :o-\n\
        `.//.   oh++++yy    .+/`\n\
           `:///o+o+oo+++/:/:`\n\
              /o+o+oo++o+o\n\
         `://o/os++++/oos/s/:-\n\
       .--` //+osoooo+oo++o+`-/-\n\
    `:+:.  -+o/+sooooooso+oo` `:/..\n\
    `:-    oo//ossosoosssooo/   `+-\n\
          /+oo+osyssoysysso++/\n\
         +o/+-oossssooso+o+o+o-\n\
        ++oy/::oossssss++:-+o++`\n\
       /++os/::/s+syos+o-../o///`\n\
      /+/ooo+-:::ooso+/.--.+++/+/\n\
     :/://++--::/--+o--..--+/++://`\n\
   `+//:++/+-:-.:.:++:--::://+//-/+-\n\
  .++:--++++.----:/://----./:/++--/+:\n\
 .+/::-/++/:`-.-.+///:/--.`.+/++/.-:+:\n\
 o:::--o++/---..-/+//o+..`../++/+-.--o-\n\
-:-:-.+/+/:....`+/+//+/--:..-:/+/:-.`-+.\n\
---:/-+/:-:--.--+://:+/--..-:--+:/...`.:\n\
 .---+/-..:.-`.:++//:+/-..------:/-.----\n\
    -//-.-/.-...///+:/:..``--.-.::-```\n\
    +/-.-.--.-.-:+///o-.`.--:...`-:\n\
   .+/--.--:---.-+///:.``.`.:..---:.\n\
   :/:..----:-...--:-.-..-.`-``....:.\n\
   .--`..:--...-.:-`.-.-...`.....--.\n\
    -:--.---..-..     `..````....`:\n\
      ...-..``          `..:-.`--.      ')

    print('\
     ___ _        _ _                        \n\
    | _ \ |_ _  _| | |_____ _____ _ _ __ _   \n\
    |  _/ . \  | | | / _ \ \ / -_) ._/ _` |  \n\
    |_| |_||_\_, |_|_\___/_\_\___|_| \__,_|  \n\
            |__/                            \n\
    ')

    # print_logo()
import os
import sys
from ROOT import ROOT, gInterpreter, gSystem, RooFit

logger.debug("Include headers")
path = os.path.join(os.path.dirname(
    os.path.abspath(__file__)), "include/Phylloxera")
for afile in os.listdir(path):
    if afile.endswith(".hh"):
        logger.debug("\t->{}".format(os.path.join(path, afile)))
        # gInterpreter.ProcessLine(
        #     '#include "{}"'.format(os.path.join(path, afile)))
        gInterpreter.LoadMacro(os.path.join(path, afile))

logger.debug("Import lib")
path = os.path.join(os.path.dirname(
    os.path.abspath(__file__)), "lib")
for afile in os.listdir(path):
    if afile.endswith(".dylib"):
        logger.debug("\t->{}".format(os.path.join(path, afile)))
        gSystem.Load(os.path.join(path, afile))
# logger.info("Almost all set!")

# from ROOT import Phylloxera
# print(sys.modules['ROOT.Phylloxera'])

logger.info("All set!")

# from ROOT import Phylloxera


# class PhylloxeraInterface(Phylloxera.PdfFactory):
#     def __init__(self):
#         Phylloxera.PdfFactory.__init__()
#         print("hello, this is the interface")
#         print(self.getDouble())

# def getDouble(self):
#     return self.getDouble()


# if __name__ == "__main__":
#     addPhylloxeraToRoot()


# class Phylloxera:
#     def __init__(self):
#         self.loadHeaders()
#         self.loadLibraries()
#         self.test()

#     def loadHeaders(self):
#         import os
#         import sys
#         from ROOT import ROOT, gInterpreter, gSystem, RooFit

#         logger.debug("Include headers")
#         path = os.path.join(os.path.dirname(
#             os.path.abspath(__file__)), "include/Phylloxera")
#         for afile in os.listdir(path):
#             if afile.endswith(".hh"):
#                 logger.debug("\t->{}".format(os.path.join(path, afile)))
#                 gInterpreter.ProcessLine(
#                     '#include "{}"'.format(os.path.join(path, afile)))

#     def loadLibraries(self):
#         import os
#         import sys
#         from ROOT import ROOT, gInterpreter, gSystem, RooFit
#         logger.debug("Import lib")
#         path = os.path.join(os.path.dirname(
#             os.path.abspath(__file__)), "lib")
#         for afile in os.listdir(path):
#             if afile.endswith(".dylib"):
#                 logger.debug("\t->{}".format(os.path.join(path, afile)))
#                 gSystem.Load(os.path.join(path, afile))
#         logger.info("Almost all set!")

#         from ROOT import Phylloxera
#         print(sys.modules['ROOT.Phylloxera'])

#         logger.info("All set!")

#     def test(self):
#         a = ROOT.KrTest()
#         print(a)