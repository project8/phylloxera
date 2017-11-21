#include "TObject.h"
#include "TFile.h"

#include "logger.hh"

namespace Phylloxera
{
LOGGER(rfr, "RootFileInterface");

class RootFileInterface : public TObject
{
public:
  enum FileOption
  {
    RECREATE,
    OPEN,
    WRITE
  };
  RootFileInterface(){};
  RootFileInterface(const char *, RootFileInterface::FileOption = FileOption::RECREATE);

  TFile *GetTFile() { return file; }

private:
  TFile *file;
};
}