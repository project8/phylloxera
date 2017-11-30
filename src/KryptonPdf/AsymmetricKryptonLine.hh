#ifndef ASYMMETRICKRYPTONLINE_HH
#define ASYMMETRICKRYPTONLINE_HH

#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "RooBreitWigner.h"

namespace Phylloxera
{
class AsymmetricKryptonLine : public RooAbsPdf
{
public:
  AsymmetricKryptonLine(){};
  AsymmetricKryptonLine(const char *name, const char *title,
                        RooAbsReal &_KE, RooAbsReal &_mean, RooAbsReal &_HWHM, RooAbsReal &_alpha);
  AsymmetricKryptonLine(const AsymmetricKryptonLine &other, const char *name = 0);
  virtual TObject *clone(const char *newname) const { return new AsymmetricKryptonLine(*this, newname); }
  inline virtual ~AsymmetricKryptonLine(){};

  // Int_t getAnalyticalIntegral(RooArgSet &allVars, RooArgSet &analVars, const char *rangeName = 0) const;
  // Double_t analyticalIntegral(Int_t code, const char *rangeName = 0) const;
  Double_t evaluate() const;

protected:
  RooRealProxy KE;
  RooRealProxy mean;
  RooRealProxy HWHM;
  RooRealProxy alpha; //Asymmetry coefficient

public:
  ClassDef(AsymmetricKryptonLine, 1)
};
}
#endif