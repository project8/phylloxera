// Your description goes here...

#include "AsymmetricKryptonLine.hh"
#include "RooAbsReal.h"
#include <math.h>
#include "TMath.h"
#include "TClass.h"
#include "Riostream.h"
#include "RooFit.h"

ClassImp(AsymmetricKryptonLine);

// namespace Phylloxera
// {

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
// }
