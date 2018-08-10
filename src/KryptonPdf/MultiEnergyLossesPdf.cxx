// Your description goes here...

#include "MultiEnergyLossesPdf.hh"
#include "RooAbsReal.h"
#include <math.h>
#include "TMath.h"
#include "Riostream.h"
#include "RooFit.h"

#include <iostream>

ClassImp(MultiEnergyLossesPdf);

MultiEnergyLossesPdf::MultiEnergyLossesPdf(const char *name, const char *title,
                                           RooAbsReal &_x,
                                           RooAbsReal &_mean1, RooAbsReal &_mean2,
                                           RooAbsReal &_width1, RooAbsReal &_width2,
                                           RooAbsReal &_amplitude1, RooAbsReal &_amplitude2,
                                           double proba,
                                           int maxNumberOfLosses) : RooAbsPdf(name, title),
                                                                    fX("x", "x", this, _x),
                                                                    fMean1("mean1", "Mean1", this, _mean1),
                                                                    fMean2("mean2", "Mean2", this, _mean2),
                                                                    fWidth1("width1", "Width1", this, _width1),
                                                                    fWidth2("width2", "Width2", this, _width2),
                                                                    fAmplitude1("amplitude1", "Amplitude1", this, _amplitude1),
                                                                    fAmplitude2("amplitude2", "Amplitude2", this, _amplitude2),
                                                                    fIsPdfInitiated(false),
                                                                    fEnergyLossesProba(proba)
                                                                    // fEnergyLossesProba(EnergyLossPdf("energyLossPdf", "energyLossPdf", fX, fMean1, fMean2, fWidth1, fWidth2, fAmplitude1, fAmplitude2))
{
    // fEnergyLossesProba = EnergyLossPdf("energyLossPdf", "energyLossPdf", fX, fMean1, fMean2, fWidth1, fWidth2, fAmplitude1, fAmplitude2);

    // for
    std::cout << "Hello" << std::endl;
}

MultiEnergyLossesPdf::MultiEnergyLossesPdf(const MultiEnergyLossesPdf &other, const char *name) : RooAbsPdf(other, name),
                                                                                                  fX("x", this, other.fX),
                                                                                                  fMean1("mean1", this, other.fMean1),
                                                                                                  fMean2("mean2", this, other.fMean2),
                                                                                                  fWidth1("width1", this, other.fWidth1),
                                                                                                  fWidth2("width2", this, other.fWidth2),
                                                                                                  fAmplitude1("amplitude1", this, other.fAmplitude1),
                                                                                                  fAmplitude2("amplitude2", this, other.fAmplitude2),
                                                                                                  fIsPdfInitiated(other.fIsPdfInitiated),
                                                                                                  fEnergyLossesProba(other.fEnergyLossesProba),
                                                                                                  fPdf(other.fPdf)

{
}

Double_t MultiEnergyLossesPdf::evaluate() const
{

    return 0;
}