// Your description goes here...

#include "AsymmetricKryptonLine.hh"
#include "RooAbsReal.h"
#include <math.h>
#include "TMath.h"

namespace Phylloxera
{
AsymmetricKryptonLine::AsymmetricKryptonLine(const char *name, const char *title,
                                             RooAbsReal &_KE, RooAbsReal &_mean, RooAbsReal &_HWHM, RooAbsReal &_alpha) : RooAbsPdf(name, title),
                                                                                                                          KE("KE", "KE", this, _KE),
                                                                                                                          mean("mean", "Mean", this, _mean),
                                                                                                                          HWHM("HWHM", "HWHM", this, _HWHM),
                                                                                                                          alpha("alpha", "Alpha", this, _alpha)
{
}

AsymmetricKryptonLine::AsymmetricKryptonLine(const AsymmetricKryptonLine &other, const char *name) : RooAbsPdf(other, name),
                                                                                                     KE("KE", this, other.KE),
                                                                                                     mean("mean", this, other.mean),
                                                                                                     HWHM("HWHM", this, other.HWHM),
                                                                                                     alpha("alpha", this, other.alpha)
{
}

Double_t AsymmetricKryptonLine::evaluate() const
{
    Double_t arg = KE - mean;
    return 1. / (TMath::Pi() * HWHM) / TMath::Power(1. + TMath::Power(arg / HWHM, 2), (1. - alpha) / 2.) * (TMath::Cos(TMath::Pi() * alpha / 2. + (1. - alpha) * TMath::ATan(arg / HWHM)));
}

////////////////////////////////////////////////////////////////////////////////

// Int_t AsymmetricKryptonLine::getAnalyticalIntegral(RooArgSet &allVars, RooArgSet &analVars, const char * /*rangeName*/) const
// {
//     if (matchArgs(allVars, analVars, KE))
//         return 1;
//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////

// Double_t AsymmetricKryptonLine::analyticalIntegral(Int_t code, const char *rangeName) const
// {
//     switch (code)
//     {
//     case 1:
//     {
//         return 1. / TMath::Pi() * (atan((KE.max(rangeName) - mean) / HWHM) - atan((KE.min(rangeName) - mean) / HWHM));
//     }
//     }

//     assert(0);
//     return 0;
// }
}