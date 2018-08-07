#ifndef ENERGYLOSSPDF_HH
#define ENERGYLOSSPDF_HH

#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "RooBreitWigner.h"

// namespace Phylloxera
// {
class EnergyLossPdf : public RooAbsPdf
{
public:
  EnergyLossPdf(){};
  EnergyLossPdf(const char *name, const char *title,
                        RooAbsReal &_KE, RooAbsReal &_mean, RooAbsReal &_HWHM, RooAbsReal &_alpha);
  EnergyLossPdf(const EnergyLossPdf &other, const char *name = 0);
  virtual TObject *clone(const char *newname) const { return new EnergyLossPdf(*this, newname); }
  inline virtual ~EnergyLossPdf(){};

  Double_t evaluate() const;

protected:
  RooRealProxy KE;
  RooRealProxy mean;
  RooRealProxy HWHM;
  RooRealProxy alpha; //Asymmetry coefficient

public:
  ClassDef(EnergyLossPdf, 1)
};
// }
#endif