/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef REALTRITIUMFREQUENCYSPECTRUM
#define REALTRITIUMFREQUENCYSPECTRUM

#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "RooArgSet.h"


/*!
@class RealTritiumFrequencySpectrum
@author C. Claessens

@brief
Defines realistic sprectral shape for Tritium beta decay in frequency
@details
The Tritium spectrum shape that includes the R-factor is computed in the frequency domain using the CRES cyclotron frequency to energy relation.
The B field is given in T, frequency in Hz and both kinetic energy and end-point are in eV.
*/
class RealTritiumFrequencySpectrum : public RooAbsPdf
{
public:
  RealTritiumFrequencySpectrum(){};
  RealTritiumFrequencySpectrum(const char *name, const char *title,
                      RooAbsReal &_F,
                      RooAbsReal &_B,
                      RooAbsReal &_Q,
                      RooAbsReal &_mbeta);
  RealTritiumFrequencySpectrum(const RealTritiumFrequencySpectrum &other, const char *name = 0);
  virtual TObject *clone(const char *newname) const { return new RealTritiumFrequencySpectrum(*this, newname); }
  // inline virtual ~RealTritiumFrequencySpectrum(){};

protected:
  RooRealProxy F;
  RooRealProxy B;
  RooRealProxy Q;
  RooRealProxy mbeta;




  mutable double KE;
  mutable double y;


public:
  Double_t evaluate() const;
  ClassDef(RealTritiumFrequencySpectrum, 1) // Tritium spectrum pdf based in frequency
};
// }

#endif
