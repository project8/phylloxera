// Your description goes here...

#include "Riostream.h"
#include "TROOT.h"

#include "EnergyLossPdf.hh"
#include "RooAbsReal.h"
#include <math.h>
#include "TMath.h"
#include "TClass.h"

#include "TF1.h"
#include "Math/WrappedTF1.h"
#include "Math/BrentRootFinder.h"

ClassImp(EnergyLossPdf);

// namespace Phylloxera
// {

EnergyLossPdf::EnergyLossPdf(const char *name, const char *title,
                             RooAbsReal &_x,
                             RooAbsReal &_mean1, RooAbsReal &_mean2,
                             RooAbsReal &_width1, RooAbsReal &_width2,
                             RooAbsReal &_amplitude1, RooAbsReal &_amplitude2,
                             RooAbsReal &_epsilonc) : RooAbsPdf(name, title),
                                                      fX("x", "x", this, _x),
                                                      fMean1("mean1", "Mean1", this, _mean1),
                                                      fMean2("mean2", "Mean2", this, _mean2),
                                                      fWidth1("width1", "Width1", this, _width1),
                                                      fWidth2("width2", "Width2", this, _width2),
                                                      fAmplitude1("amplitude1", "Amplitude1", this, _amplitude1),
                                                      fAmplitude2("amplitude2", "Amplitude2", this, _amplitude2),
                                                      fEpsilonCut("epsilonc", "Epsilon cut", this, _epsilonc)
{
    // TF1 f("Sin Function", "log([4]) - x)", fMean1, fMean1);
    // f.SetParameter(0, 10);
    // ROOT::Math::WrappedTF1 wf1(f);

    // // Create the Integrator
    // ROOT::Math::BrentRootFinder brf;

    // // Set parameters of the method
    // brf.SetFunction(wf1, TMath::PiOver2(), TMath::TwoPi());
    // brf.Solve();

    // std::cout << brf.Root() << std::endl;
}

EnergyLossPdf::EnergyLossPdf(const EnergyLossPdf &other, const char *name) : RooAbsPdf(other, name),
                                                                             fX("x", this, other.fX),
                                                                             fMean1("mean1", this, other.fMean1),
                                                                             fMean2("mean2", this, other.fMean2),
                                                                             fWidth1("width1", this, other.fWidth1),
                                                                             fWidth2("width2", this, other.fWidth2),
                                                                             fAmplitude1("amplitude1", this, other.fAmplitude1),
                                                                             fAmplitude2("amplitude2", this, other.fAmplitude2),
                                                                             fEpsilonCut("epsilonc", this, other.fEpsilonCut)
{
}

Double_t EnergyLossPdf::evaluate() const
{
    // if (fX < fEpsilonCut)
    // {
    //     return fAmplitude1 * TMath::Gaus(fX, fMean1, fWidth1);
    // }
    // else
    // {
    //     return fAmplitude2 * TMath::CauchyDist(fX, fMean2, fWidth2);
    // }
    // return 0;
    return TMath::Max(fAmplitude1 * TMath::Gaus(fX, fMean1, fWidth1),fAmplitude2 * TMath::CauchyDist(fX, fMean2, fWidth2));

}
