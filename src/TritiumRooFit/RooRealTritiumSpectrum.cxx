#include "TROOT.h"

#include "RooRealTritiumSpectrum.hh"
#include "RooAbsReal.h"
#include <math.h>
#include "TMath.h"

#include "TritiumSpectrum.cpp"

RooRealTritiumSpectrum::RooRealTritiumSpectrum(const char *name, const char *title,
                                               RooAbsReal &_KE,
                                               RooAbsReal &_Q,
                                               RooAbsReal &_mbeta) : RooAbsPdf(name, title),
                                                                     KE("KE", "KE", this, _KE),
                                                                     Q("Q", "Q", this, _Q),
                                                                     mbeta("mbeta", "mbeta", this, _mbeta)
{
}

RooRealTritiumSpectrum::RooRealTritiumSpectrum(const RooRealTritiumSpectrum &other, const char *name) : RooAbsPdf(other, name),
                                                                                                        KE("KE", this, other.KE),
                                                                                                        Q("Q", this, other.Q),
                                                                                                        mbeta("mbeta", this, other.mbeta)
{
}

Double_t RooRealTritiumSpectrum::evaluate() const
{
    if (TMath::Power(Q - KE, 2) < TMath::Power(mbeta, 2) || Q - KE < 0 || KE < 0.)
    {
        return 0.;
    }
    return TritiumSpectrumShape(KE, Q, 1, mbeta);
}
// }