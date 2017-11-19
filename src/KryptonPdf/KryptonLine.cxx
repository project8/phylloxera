// Your description goes here...

#include "Riostream.h"
#include "TROOT.h"

#include "KryptonLine.hh"
#include "RooAbsReal.h"
#include <math.h>
#include "TMath.h"

namespace Phylloxera
{
KryptonLine::KryptonLine(const char *name, const char *title,
                         RooAbsReal &_KE, RooAbsReal &_mean, RooAbsReal &_HWHM) : RooAbsPdf(name, title),
                                                                                  KE("KE", "KE", this, _KE),
                                                                                  mean("mean", "Mean", this, _mean),
                                                                                  HWHM("HWHM", "HWHM", this, _HWHM)
{
}

KryptonLine::KryptonLine(const KryptonLine &other, const char *name) : RooAbsPdf(other, name),
                                                                       KE("KE", this, other.KE),
                                                                       mean("mean", this, other.mean),
                                                                       HWHM("HWHM", this, other.HWHM)
{
}

Double_t KryptonLine::evaluate() const
{
    Double_t arg = KE - mean;
    return 1. / (TMath::Pi() * HWHM) / (1. + TMath::Power(arg / HWHM, 2));
}

////////////////////////////////////////////////////////////////////////////////

Int_t KryptonLine::getAnalyticalIntegral(RooArgSet &allVars, RooArgSet &analVars, const char * /*rangeName*/) const
{
    if (matchArgs(allVars, analVars, KE))
        return 1;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

Double_t KryptonLine::analyticalIntegral(Int_t code, const char *rangeName) const
{
    switch (code)
    {
    case 1:
    {
        return 1. / TMath::Pi() * (atan((KE.max(rangeName) - mean) / HWHM) - atan((KE.min(rangeName) - mean) / HWHM));
    }
    }

    assert(0);
    return 0;
}
}