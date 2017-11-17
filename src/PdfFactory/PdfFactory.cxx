#include "PdfFactory.hh"

#include "RooBreitWigner.h"
#include "RooGaussian.h"

namespace Phylloxera
{

template <class PdfClass>
RooFFTConvPdf *PdfFactory::GetSmearedPdf(const char *name, const char *smearingType, RooRealVar *variable, PdfClass *pdf, RooRealVar *smearingVar, int numberBinsCache)
{
    variable->setBins(numberBinsCache, "cache");

    RooRealVar *smearingCenter = new RooRealVar("mean", "mean", 0.);

    switch (smearingType)
    {
    case "Cauchy":
        RooBreitWigner *tCauchy = new RooBreitWigner("tCauchy", "Cauchy", variable, smearingCenter, smearingVar);
        return new RooFFTConvPdf(name, name, variable, pdf, tCauchy);
    default:
        RooGaussian *tCauchy = new RooGaussian("tCauchy", "Cauchy", variable, , smearingCentersmearingVar);
        return new RooFFTConvPdf(name, name, variable, pdf, tCauchy);
    }
}
}