/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

// Your description goes here...

#include "Riostream.h"
#include "TROOT.h"

#include "SimpleTritiumSpectrum.hh"
#include "RooAbsReal.h"
#include <math.h>
#include "TMath.h"

//ClassImp(SimpleTritiumSpectrum);

namespace Phylloxera
{
SimpleTritiumSpectrum::SimpleTritiumSpectrum(const char *name, const char *title,
                                             RooAbsReal &_KE,
                                             RooAbsReal &_Q,
                                             RooAbsReal &_mbeta) : RooAbsPdf(name, title),
                                                                   KE("KE", "KE", this, _KE),
                                                                   Q("Q", "Q", this, _Q),
                                                                   mbeta("mbeta", "mbeta", this, _mbeta)
{
}

SimpleTritiumSpectrum::SimpleTritiumSpectrum(const SimpleTritiumSpectrum &other, const char *name) : RooAbsPdf(other, name),
                                                                                                     KE("KE", this, other.KE),
                                                                                                     Q("Q", this, other.Q),
                                                                                                     mbeta("mbeta", this, other.mbeta)
{
}

Double_t SimpleTritiumSpectrum::evaluate() const
{
    if (TMath::Power(Q - KE, 2) < TMath::Power(mbeta, 2) || Q - KE < 0 || KE < 0.)
    {
        return 0.;
    }
    return (Q - KE) * TMath::Sqrt(TMath::Power(Q - KE, 2) - TMath::Power(mbeta, 2));
}
}