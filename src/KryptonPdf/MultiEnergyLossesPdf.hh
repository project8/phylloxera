#ifndef MULTIENERGYLOSSESPDF_HH
#define MULTIENERGYLOSSESPDF_HH

#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "RooFFTConvPdf.h"

// namespace Phylloxera
// {
class MultiEnergyLossesPdf : public RooAbsPdf
{
public:
  MultiEnergyLossesPdf(){};
  MultiEnergyLossesPdf(const char *name, const char *title,
                RooAbsReal &_x,
                RooAbsReal &_mean1, RooAbsReal &_mean2,
                RooAbsReal &_width1, RooAbsReal &_width2,
                RooAbsReal &_amplitude1, RooAbsReal &_amplitude2,
                RooAbsReal &_epsilonc,
                double proba,
                int maxNumberOfLosses = 3);
  MultiEnergyLossesPdf(const MultiEnergyLossesPdf &other, const char *name = 0);
  virtual TObject *clone(const char *newname) const { return new MultiEnergyLossesPdf(*this, newname); }
  inline virtual ~MultiEnergyLossesPdf(){};

  Double_t evaluate() const;


protected:
  RooRealProxy fX;
  RooRealProxy fMean1;
  RooRealProxy fMean2;
  RooRealProxy fWidth1;
  RooRealProxy fWidth2;
  RooRealProxy fAmplitude1;
  RooRealProxy fAmplitude2;
  RooRealProxy fEpsilonCut;

  bool fIsPdfInitiated;
  int fMaxNumberOfLosses;
  double fEnergyLossesProba;
  RooFFTConvPdf fPdf;

public:
  ClassDef(MultiEnergyLossesPdf, 1)
};
// }
#endif