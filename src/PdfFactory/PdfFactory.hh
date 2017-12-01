#ifndef PDFFACTORY
#define PDFFACTORY

// #include "TObject.h"
#include <iostream>
#include "logger.hh"

#include "RooGaussian.h"
#include "RooRealVar.h"
#include "RooFFTConvPdf.h"
#include "RooAddPdf.h"

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
    RooFFTConvPdf *GetSmearedPdf(const char *, SmearingType, RooRealVar *, PdfClass *, RooRealVar *, RooRealVar *, int = 10000);
    template <class PdfClass>
    RooAddPdf *AddBackground(const char *, RooRealVar *, PdfClass *, RooRealVar *, RooRealVar *, int = 10000);

  protected:
    const char *fName;
    ClassDef(PdfFactory, 1)
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
        LINFO(pdffactory, "Creating " << name << ": Cauchy convoluted with " << pdf->GetName());
        delete tGaussian;
        return new RooFFTConvPdf(name, name, *variable, *pdf, *tCauchy);
    case Gaussian:
        LINFO(pdffactory, "Creating " << name << ": Normal convoluted with " << pdf->GetName());
        delete tCauchy;
        return new RooFFTConvPdf(name, name, *variable, *pdf, *tGaussian);
    };
    return 0;
};

template <class PdfClass>
RooAddPdf *PdfFactory::AddBackground(const char *name, RooRealVar *variable, PdfClass *pdf, RooRealVar *backgroundFraction)
{
    RooChebychev *bkg = new RooChebychev("bkg", "background p.d.f.", *variable);
    RooRealVar bkgfrac("sigfrac", "fraction of background", 0.2, 0., 1.);
    RooAddPdf *model = new RooAddPdf("model", "model", RooArgList(*pdf, *bkg), RooArgList(*nsig, *nbkg));
}

template RooFFTConvPdf *PdfFactory::GetSmearedPdf<RooGaussian>(const char *name,
                                                               SmearingType type,
                                                               RooRealVar *variable,
                                                               RooGaussian *pdf,
                                                               RooRealVar *smearingCenter,
                                                               RooRealVar *smearingVar,
                                                               int numberBinsCache);
}
#endif