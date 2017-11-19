#ifndef PDFFACTORY
#define PDFFACTORY

#include "TObject.h"
#include <iostream>
#include "logger.hh"

#include "RooGaussian.h"
#include "RooRealVar.h"
#include "RooFFTConvPdf.h"
#include "RooBreitWigner.h"
#include "RooGaussian.h"

LOGGER(pdffactory, "PdfFactory");

namespace Phylloxera
{
class PdfFactory : public TObject
{
  public:
    enum SmearingType
    {
        Cauchy,
        Lorentzian,
        Gaussian
    };
    PdfFactory() { std::cout << "Hello you!" << std::endl; };
    PdfFactory(const char *name, const char *title);
    PdfFactory(const PdfFactory &other, const char *name = 0);
    virtual TObject *clone(const char *newname) const { return new PdfFactory(*this, newname); }
    inline virtual ~PdfFactory(){};

    template <class PdfClass>
    PdfClass createPdf(PdfClass);

    template <class PdfClass>
    RooFFTConvPdf *GetSmearedPdf(const char *, SmearingType, RooRealVar *, PdfClass *, RooRealVar *, RooRealVar *, int = 10000);
};

template <class PdfClass>
PdfClass PdfFactory::createPdf(PdfClass object)
{
    return PdfClass(object, "test");
};

template <class PdfClass>
RooFFTConvPdf *PdfFactory::GetSmearedPdf(const char *name, SmearingType type, RooRealVar *variable, PdfClass *pdf, RooRealVar *smearingCenter, RooRealVar *smearingVar, int numberBinsCache)
{
    variable->setBins(numberBinsCache, "cache");

    // RooRealVar *smearingCenter = new RooRealVar("mean", "mean", 0.);

    RooBreitWigner *tCauchy = new RooBreitWigner("tCauchy", "Cauchy", *variable, *smearingCenter, *smearingVar);
    RooGaussian *tGaussian = new RooGaussian("tGaussian", "Gaussian", *variable, *smearingCenter, *smearingVar);

    switch (type)
    {
    case Cauchy:
    case Lorentzian:
        LDEBUG(pdffactory, "Creating " << name << ": Cauchy convoluted with " << pdf->GetName());
        delete tGaussian;
        return new RooFFTConvPdf(name, name, *variable, *pdf, *tCauchy);
    case Gaussian:
        LDEBUG(pdffactory, "Creating " << name << ": Normal convoluted with " << pdf->GetName());
        delete tCauchy;
        return new RooFFTConvPdf(name, name, *variable, *pdf, *tGaussian);
    };
};
}
#endif