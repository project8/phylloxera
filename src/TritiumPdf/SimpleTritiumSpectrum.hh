/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef SIMPLETRITIUMSPECTRUM
#define SIMPLETRITIUMSPECTRUM

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"

// namespace Phylloxera
// {
class SimpleTritiumSpectrum : public RooAbsPdf
{
public:
  SimpleTritiumSpectrum(){};
  SimpleTritiumSpectrum(const char *name, const char *title,
                        RooAbsReal &_KE,
                        RooAbsReal &_Q,
                        RooAbsReal &_mbeta);
  SimpleTritiumSpectrum(const SimpleTritiumSpectrum &other, const char *name = 0);
  virtual TObject *clone(const char *newname) const { return new SimpleTritiumSpectrum(*this, newname); }
  inline virtual ~SimpleTritiumSpectrum(){};

protected:
  RooRealProxy KE;
  RooRealProxy Q;
  RooRealProxy mbeta;

  Double_t evaluate() const;

  ClassDef(SimpleTritiumSpectrum, 1) // Your description goes here...
};
// }

#endif
