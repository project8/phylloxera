#ifndef TRITIUMSPECTRUM
#define TRITIUMSPECTRUM

#include "TMath.h"

// namespace Phylloxera
// {

// Formulas extracted from Robertson, R. G. H., & Knapp, D. A. (1988).
// Direct Measurements of Neutrino Mass. Annual Review of Nuclear and Particle Science, 38(1), 185–215.
// http://doi.org/10.1146/annurev.ns.38.120188.001153

double DiracFermiFunction(double E, double Z, double m);

double RFactor(double E, double Z);

double TritiumSpectrumShape(double E, double E0, double Z, double mbeta);

Double_t TritiumSpectrumShape(Double_t *x, Double_t *par);
// }
#endif
