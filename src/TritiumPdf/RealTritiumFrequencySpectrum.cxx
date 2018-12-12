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
{
    multiplyEfficiency = false;
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

    if (false)
    {
        //int L = eff_coeff.size();
        //std::cout<<L<<std::endl;
        //this->CalculateEfficiency(F);
        //std::cout<<efficiency_factor<<std::endl;
        //std::cout<<eff_coeff.at(1)<<std::endl;
        return TritiumSpectrumShape(KE, Q, 1, mbeta) * efficiency_factor;
    }
    return TritiumSpectrumShape(KE, Q, 1, mbeta);
}

void RealTritiumFrequencySpectrum::SetEfficiencyCoefficients(RooArgSet *a)
{
    /*double b = a->getRealValue("0");
    double b1 = a->getRealValue("1");
    std::cout<<b<<std::endl;
    std::cout<<b1<<std::endl;*/

    multiplyEfficiency = true;

    int N = a->getSize();

    std::cout<<"trying to get arglist content in loop"<<std::endl;
    std::cout<<N<<std::endl;

    for (int i = 0; i < N; i++)
    {
        std::string s = std::to_string(i);
        char const *pchar = s.c_str();
        double* c = new double(a->getRealValue(pchar));
        std::cout<<*c<<std::endl;
        eff_coeff.push_back(*c);

    }

    int M = eff_coeff.size();
    std::cout<<M<<eff_coeff.at(1)<<std::endl;
}
void RealTritiumFrequencySpectrum::CalculateEfficiency(double f) const
{
    int L = eff_coeff.size();
    std::cout<<L<<std::endl;
    efficiency_factor = 0;
    for (int i = 0; i < L; i++)
    {
        std::cout<<" F "<<f<<std::endl;
        efficiency_factor += eff_coeff.at(i) * TMath::Power(f, i);
    }

}


// }
