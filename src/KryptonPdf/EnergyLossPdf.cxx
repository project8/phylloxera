// Your description goes here...

#include "EnergyLossPdf.hh"
#include "RooAbsReal.h"
#include <math.h>
#include "TMath.h"
#include "TClass.h"
#include "Riostream.h"
#include "RooFit.h"

ClassImp(EnergyLossPdf);

// namespace Phylloxera
// {

EnergyLossPdf::EnergyLossPdf(const char *name, const char *title,
                             RooAbsReal &_x,
                             RooAbsReal &_mean1, RooAbsReal &_mean2,
                             RooAbsReal &_width1, RooAbsReal &_width2,
                             RooAbsReal &_amplitude1, RooAbsReal &_amplitude2) : RooAbsPdf(name, title),
                                                                                 x("x", "x", this, _x),
                                                                                 mean1("mean1", "Mean1", this, _mean1),
                                                                                 mean2("mean2", "Mean2", this, _mean2),
                                                                                 width1("width1", "Width1", this, _width1),
                                                                                 width2("width2", "Width2", this, _width2),
                                                                                 amplitude1("amplitude1", "Amplitude1", this, _amplitude1),
                                                                                 amplitude2("amplitude2", "Amplitude2", this, _amplitude2),
                                                                                 epsilonc("epsilonc", "Epsilon cut", this, _epsilonc)
{
}

EnergyLossPdf::EnergyLossPdf(const EnergyLossPdf &other, const char *name) : RooAbsPdf(other, name),
                                                                             KE("KE", this, other.KE),
                                                                             mean1("mean1", this, other.mean1),
                                                                             mean2("mean2", this, other.mean2),
                                                                             width1("width1", this, other.width1),
                                                                             width2("width2", this, other.width2),
                                                                             amplitude1("amplitude1", this, other.amplitude1),
                                                                             amplitude2("amplitude2", this, other.amplitude2),
                                                                             epsilonc("epsilonc", this, other.epsilonc)
{
}

Double_t EnergyLossPdf::evaluate() const
{
    if (x < epsilonc)
    {
        return amplitude1 / TMath::Gaus(x, mean1, sigma1);
    }
    else
    {
        // return amplitude2 * TMath::CauchyDist;
        return 0;
    }
}
// }