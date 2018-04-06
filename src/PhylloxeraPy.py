
import os
import sys
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

def print_image():
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

def print_logo():
    print('\
     ___ _        _ _                        \n\
    | _ \ |_ _  _| | |_____ _____ _ _ __ _   \n\
    |  _/ . \  | | | / _ \ \ / -_) ._/ _` |  \n\
    |_| |_||_\_, |_|_\___/_\_\___|_| \__,_|  \n\
            |__/                            \n\
    ')


def loadLibraries(silence=False):
    import ROOT
    if hasattr(ROOT,"PdfFactory"):
        logger.debug("Libraries already loaded...")
        return
    if silence:
        print_logo()        
        from ROOT import RooMsgService
        RooMsgService.instance().setSilentMode(True)
        RooMsgService.instance().setGlobalKillBelow(5)
        logger.setLevel(logging.INFO)
    else:
        print_image()
        print_logo()

    from ROOT import gSystem, gInterpreter
    logger.debug("Import libraries...")
    path = os.path.join(os.path.dirname(
        os.path.abspath(__file__)), "lib")
    for afile in os.listdir(path):
        if afile.endswith(".dylib") or afile.endswith(".so"):
            logger.debug("\t->{}".format(os.path.join(path, afile)))
            gSystem.Load(os.path.join(path, afile))

    logger.info("All set!")
