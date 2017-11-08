#ifndef ROOKRYPTONLINE_HH
#define ROOKRYPTONLINE_HH

#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "RooAbsPdf.h"

class RooKryptonLine : public RooAbsPdf
{
  public:
    RooKryptonLine(){};
    RooKryptonLine(const char *name, const char *title,
                   RooAbsReal &_KE);
    RooKryptonLine(const RooKryptonLine &other, const char *name = 0);
    virtual TObject *clone(const char *newname) const { return new RooKryptonLine(*this, newname); }
    inline virtual ~RooKryptonLine(){};

  protected:
    RooRealProxy KE;

    Double_t evaluate() const;
};

#endif