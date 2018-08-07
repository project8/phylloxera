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
                RooAbsReal &_x, 
                RooAbsReal &_mean1, RooAbsReal &_mean2, 
                RooAbsReal &_width1, RooAbsReal &_width2, 
                RooAbsReal &_amplitude1, RooAbsReal &_amplitude2, 
                RooAbsReal &_epsilonc);
  EnergyLossPdf(const EnergyLossPdf &other, const char *name = 0);
  virtual TObject *clone(const char *newname) const { return new EnergyLossPdf(*this, newname); }
  inline virtual ~EnergyLossPdf(){};

  Double_t evaluate() const;

protected:
  RooRealProxy x;
  RooRealProxy mean1;
  RooRealProxy mean2;
  RooRealProxy width1;
  RooRealProxy width2;
  RooRealProxy amplitude1;
  RooRealProxy amplitude2;
  RooRealProxy epsilonc;

public:
  ClassDef(EnergyLossPdf, 1)
};
// }
#endif