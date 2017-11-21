#include "RootFileInterface.hh"

#include <iostream>

namespace Phylloxera
{
RootFileInterface::RootFileInterface(const char *filename, RootFileInterface::FileOption option)
{
    TString tOption;
    switch (option)
    {
    default:
    case RECREATE:
        LDEBUG(rfr, "RECREATE option");
        tOption = TString("RECREATE");
        break;
    case OPEN:
        LDEBUG(rfr, "OPEN option");
        tOption = TString("OPEN");
        break;
    case WRITE:
        LDEBUG(rfr, "WRITE option");
        tOption = TString("WRITE");
        break;
    }
    file = new TFile(filename, tOption.Data());
}
}