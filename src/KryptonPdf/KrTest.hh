#ifndef KRTEST
#define KRTEST

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"

namespace Phylloxera{
class KrTest : public RooAbsPdf
{
public:
  KrTest(){};
  KrTest(const char *name, const char *title,
            RooAbsReal &_KE);
  KrTest(const KrTest &other, const char *name = 0);
  virtual TObject *clone(const char *newname) const { return new KrTest(*this, newname); }
  inline virtual ~KrTest(){};

protected:
  RooRealProxy KE;

  Double_t evaluate() const;
};
}

#endif
