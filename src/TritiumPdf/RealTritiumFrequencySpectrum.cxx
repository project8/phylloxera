#include "TROOT.h"

#include "RealTritiumFrequencySpectrum.hh"
#include "RooAbsReal.h"
#include <math.h>
#include "TMath.h"
#include "Constant.hh"
#include "TritiumSpectrum.hh"

ClassImp(RealTritiumFrequencySpectrum);

// namespace Phylloxera
// {
RealTritiumFrequencySpectrum::RealTritiumFrequencySpectrum(const char *name, const char *title,
                                         RooAbsReal &_F,
                                         RooAbsReal &_B,
                                         RooAbsReal &_Q,
                                         RooAbsReal &_mbeta) : RooAbsPdf(name, title),
                                                               F("F", "F", this, _F),
                                                               B("B", "B", this, _B),
                                                               Q("Q", "Q", this, _Q),
                                                               mbeta("mbeta", "mbeta", this, _mbeta)
{
}

RealTritiumFrequencySpectrum::RealTritiumFrequencySpectrum(const RealTritiumFrequencySpectrum &other, const char *name) : RooAbsPdf(other, name),
                                                                                               F("F", this, other.F),
                                                                                               B("B", this, other.B),
                                                                                               Q("Q", this, other.Q),
                                                                                               mbeta("mbeta", this, other.mbeta)
{
}

Double_t RealTritiumFrequencySpectrum::evaluate() const
{
    double y = (ElectronCharge()*B)/(2.0*TMath::Pi()*ElectronMassInKilogram()) * 1/F;
    double KE = (y-1)*ElectronMassIneV();

    if (TMath::Power(Q - KE, 2) < TMath::Power(mbeta, 2) || Q - KE < 0 || KE < 0.)
    {
        return 0.;
    }
    return TritiumSpectrumShape(KE, Q, 1, mbeta);
}

// }
