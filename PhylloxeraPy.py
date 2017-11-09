def print_logo():
    print('\n\
       ` .` :--..`       ...-:-`:.       \n\
      .-++: ``..//:--:/:-..   :o-       \n\
        `.//.   oh++++yy    .+/`        \n\
           `:///o+o+oo+++/:/:`          \n\
              /o+o+oo++o+o              \n\
         `://o/os++++/oos/s/:-          \n\
       .--` //+osoooo+oo++o+`-/-        \n\
    `:+:.  -+o/+sooooooso+oo` `:/..     \n\
    `:-    oo//ossosoosssooo/   `+-     \n\
          /+oo+osyssoysysso++/          \n\
         +o/+-oossssooso+o+o+o-         \n\
        ++oy/::oossssss++:-+o++`        \n\
       /++os/::/s+syos+o-../o///`       \n\
      /+/ooo+-:::ooso+/.--.+++/+/       \n\
     :/://++--::/--+o--..--+/++://`     \n\
   `+//:++/+-:-.:.:++:--::://+//-/+-    \n\
  .++:--++++.----:/://----./:/++--/+:    \n\
 .+/::-/++/:`-.-.+///:/--.`.+/++/.-:+:    \n\
 o:::--o++/---..-/+//o+..`../++/+-.--o-   \n\
-:-:-.+/+/:....`+/+//+/--:..-:/+/:-.`-+.  \n\
---:/-+/:-:--.--+://:+/--..-:--+:/...`.:  \n\
 .---+/-..:.-`.:++//:+/-..------:/-.----  \n\
    -//-.-/.-...///+:/:..``--.-.::-```   \n\
    +/-.-.--.-.-:+///o-.`.--:...`-:     \n\
   .+/--.--:---.-+///:.``.`.:..---:.    \n\
   :/:..----:-...--:-.-..-.`-``....:.   \n\
   .--`..:--...-.:-`.-.-...`.....--.    \n\
    -:--.---..-..     `..````....`:     \n\
      ...-..``          `..:-.`--.      ')

    print('\
     ___ _        _ _                        \n\
    | _ \ |_ _  _| | |_____ _____ _ _ __ _   \n\
    |  _/ . \  | | | / _ \ \ / -_) ._/ _` |  \n\
    |_| |_||_\_, |_|_\___/_\_\___|_| \__,_|  \n\
            |__/                            \n\
    ')


def main():
    print_logo()
    import os
    from ROOT import ROOT, gInterpreter, gSystem, RooFit

    print("Include headers")
    path = os.path.join(os.path.dirname(
        os.path.abspath(__file__)), "build/include/Phylloxera")
    for afile in os.listdir(path):
        if afile.endswith(".hh"):
            print("\t->{}".format(os.path.join(path, afile)))
            gInterpreter.ProcessLine(
                '#include "{}"'.format(os.path.join(path, afile)))

    print("Import lib")
    path = os.path.join(os.path.dirname(
        os.path.abspath(__file__)), "build/lib")
    for afile in os.listdir(path):
        if afile.endswith(".dylib"):
            print("\t->{}".format(afile))
            gSystem.Load(afile)


def setSilent():
    from ROOT import


if __name__ == "main":
    main()
