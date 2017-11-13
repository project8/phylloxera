#ifndef KRYPTONLINE_HH
#define KRYPTONLINE_HH

#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "RooBreitWigner.h"

class KryptonLine : public RooAbsPdf
{
public:
  KryptonLine(){};
  KryptonLine(const char *name, const char *title,
              RooAbsReal &_KE, RooAbsReal &_mean, RooAbsReal &_HWHM);
  KryptonLine(const KryptonLine &other, const char *name = 0);
  virtual TObject *clone(const char *newname) const { return new KryptonLine(*this, newname); }
  inline virtual ~KryptonLine(){};

  Int_t getAnalyticalIntegral(RooArgSet &allVars, RooArgSet &analVars, const char *rangeName = 0) const;
  Double_t analyticalIntegral(Int_t code, const char *rangeName = 0) const;
  Double_t evaluate() const;

protected:
  RooRealProxy KE;
  RooRealProxy mean;
  RooRealProxy HWHM;
};

#endif