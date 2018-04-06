#ifndef TRITIUMSPECTRUM
#define TRITIUMSPECTRUM

#include "Constant.cpp"

// namespace Phylloxera
// {

// Formulas extracted from Robertson, R. G. H., & Knapp, D. A. (1988).
// Direct Measurements of Neutrino Mass. Annual Review of Nuclear and Particle Science, 38(1), 185–215.
// http://doi.org/10.1146/annurev.ns.38.120188.001153

double DiracFermiFunction(double E, double Z, double m)
{
    double beta = TMath::Sqrt(2 * E / m);
    double eta = FineStructureConstant() * (Z + 1) / beta;
    return 2 * TMath::Pi() * eta / (1 - TMath::Exp(-2 * TMath::Pi() * eta));
}

double RFactor(double E, double Z)
{
    // Form factor to use to define the spectrum shape
    // Use this for defining the Kurie plot
    return DiracFermiFunction(E, Z, ElectronMassIneV()) * TMath::Sqrt(2 * ElectronMassIneV() * E) * (E + ElectronMassIneV());
}

double TritiumSpectrumShape(double E, double E0, double Z, double mbeta)
{
    return RFactor(E, Z) * (E0 - E) * TMath::Sqrt(TMath::Power(E0 - E, 2) - TMath::Power(mbeta, 2));
}

Double_t TritiumSpectrumShape(Double_t *x, Double_t *par)
{
    /*
    par[0]: e0 (in keV)
    par[1]: Z
    par[2]: neutrino mass
    par[3]: normalization
    */
    Float_t xx = x[0];
    if (xx > par[0])
        return 0;
    return par[3] * TritiumSpectrumShape(xx, par[0], par[1], par[2]);
}
// }
#endif