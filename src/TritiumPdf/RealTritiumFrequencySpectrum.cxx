#include "TROOT.h"

#include "RealTritiumFrequencySpectrum.hh"
#include "RooAbsReal.h"
#include "RooArgList.h"
#include "RooPolyVar.h"
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
                                                               mbeta("mbeta", "mbeta", this, _mbeta),
                                                               multiplyEfficiency(false)
                                                               //efficiency("efficiency", "efficiency", "@0 + @1*TMath::Power(@2,1)", _eff_coeff)

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
    y = (-ElectronCharge()*B)/(2.0*TMath::Pi()*ElectronMassInKilogram()) * 1/F;
    KE = (y-1)*ElectronMassIneV();
    //std::cout<<F<<" "<< KE<< " "<<TMath::Pi()<<" "<<B<<std::endl;

    if (TMath::Power(Q - KE, 2) < TMath::Power(mbeta, 2) || Q - KE < 0 || KE < 0.)
    {
        return 0.;
    }

    //RooPolyVar efficiency("efficiency", "efficiency", F, eff_coeff, 0);
    if (multiplyEfficiency)
    {
        efficiency_factor = efficiency.evaluate();
        std::cout<<efficiency_factor<<std::endl;
        return TritiumSpectrumShape(KE, Q, 1, mbeta) * efficiency_factor;
    }
    else
    {
        return TritiumSpectrumShape(KE, Q, 1, mbeta);
    }
}

void RealTritiumFrequencySpectrum::SetEfficiencyCoefficients(RooAbsReal *p0, RooAbsReal *p1, RooAbsReal *var)
{
    multiplyEfficiency = false;
    RooArgList eff_coeff(*p0, *p1, *var);
    /*unsigned N = a->getSize();

    std::cout<<N<<std::endl;

    for (int i = 0; i < N; i++)
    {
        RooAbsArg* b = *(a->at(i));
        eff_coeff.addOwned(b);
        std::cout<<eff_coeff.at(i)<<std::endl;
    }*/
    RooFormulaVar efficiency("efficiency", "efficiency", "@0 + @1*TMath::Power(@2,1)", eff_coeff);

}
/*void RealTritiumFrequencySpectrum::efficiency() const
{
    //efficiency = RooPolyVar("eff", "eff", F, eff_coeff);
    efficiency_factor = efficiency.evaluate();
}*/

// }
