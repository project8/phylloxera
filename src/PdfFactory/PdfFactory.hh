#ifndef PDFFACTORY
#define PDFFACTORY

// #include "TObject.h"
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
class PdfFactory
{
  public:
    enum SmearingType
    {
        Cauchy,
        Lorentzian,
        Gaussian
    };
    PdfFactory(const char *name = "") : fName(name) { LINFO(pdffactory, "Hello you! My name is " << name); };
    void testFunc() { std::cout << "test" << std::endl; }
    // PdfFactory(const char *, const char *);
    // PdfFactory(const char *name, const char *title) { std::cout << "Hello you!" << std::endl; };
    // PdfFactory(const PdfFactory &other, const char *name) { std::cout << "Hello you!" << std::endl; };
    // virtual PdfFactory *clone(const char *newname) const { return new PdfFactory(*this, newname); }
    inline virtual ~PdfFactory() = default;

    template <class PdfClass>
    PdfClass createPdf(PdfClass);

    template <class PdfClass>
    RooFFTConvPdf *GetSmearedPdf(const char *, SmearingType, RooRealVar *, PdfClass *, RooRealVar *, RooRealVar *, int = 10000);

  protected:
    const char *fName;
    ClassDef(PdfFactory, 1)
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
    return 0;
};

template RooGaussian PdfFactory::createPdf<RooGaussian>(RooGaussian);
template RooFFTConvPdf *PdfFactory::GetSmearedPdf<RooGaussian>(const char *name, SmearingType type, RooRealVar *variable, RooGaussian *pdf, RooRealVar *smearingCenter, RooRealVar *smearingVar, int numberBinsCache);
}
#endif