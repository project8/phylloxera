#ifndef PDFFACTORY
#define PDFFACTORY

// #include "TObject.h"
#include <iostream>
// #include "logger.hh"

#include "RooGaussian.h"
#include "RooRealVar.h"
#include "RooFFTConvPdf.h"
#include "RooAddPdf.h"

#include "RooBreitWigner.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooUniform.h"

// LOGGER(pdffactory, "PdfFactory");

// namespace Phylloxera
// {
class PdfFactory
{
  public:
    enum SmearingType
    {
        Cauchy,
        Lorentzian,
        Gaussian
    };
    PdfFactory(){};
    PdfFactory(const char *name) : fName(name){};
    inline virtual ~PdfFactory() = default;

    template <class PdfClass>
    RooFFTConvPdf *GetSmearedPdf(const char *, SmearingType, RooRealVar *, PdfClass *, RooRealVar *, RooRealVar *, int = 10000);
    template <class PdfClass>
    RooAddPdf *AddBackground(const char *, RooRealVar *, PdfClass *, RooRealVar *, RooRealVar *);

  protected:
    const char *fName;
    ClassDef(PdfFactory, 1)
};

template <class PdfClass>
RooFFTConvPdf *PdfFactory::GetSmearedPdf(const char *name, SmearingType type, RooRealVar *variable, PdfClass *pdf, RooRealVar *smearingCenter, RooRealVar *smearingVar, int numberBinsCache)
{
    variable->setBins(numberBinsCache, "cache");
    RooBreitWigner *tCauchy = new RooBreitWigner("tCauchy", "Cauchy", *variable, *smearingCenter, *smearingVar);
    RooGaussian *tGaussian = new RooGaussian("tGaussian", "Gaussian", *variable, *smearingCenter, *smearingVar);

    switch (type)
    {
    case Cauchy:
    case Lorentzian:
        // LINFO(pdffactory, "Creating " << name << ": Cauchy convoluted with " << pdf->GetName());
        delete tGaussian;
        return new RooFFTConvPdf(name, name, *variable, *pdf, *tCauchy);
    case Gaussian:
        // LINFO(pdffactory, "Creating " << name << ": Normal convoluted with " << pdf->GetName());
        delete tCauchy;
        return new RooFFTConvPdf(name, name, *variable, *pdf, *tGaussian);
    };
    return 0;
};

template RooFFTConvPdf *PdfFactory::GetSmearedPdf<RooGaussian>(const char *name,
                                                               SmearingType type,
                                                               RooRealVar *variable,
                                                               RooGaussian *pdf,
                                                               RooRealVar *smearingCenter,
                                                               RooRealVar *smearingVar,
                                                               int numberBinsCache);

template <class PdfClass>
RooAddPdf *PdfFactory::AddBackground(const char *name, RooRealVar *variable, PdfClass *pdf, RooRealVar *NSignalEvents, RooRealVar *NBkgdEvents)
{
    RooUniform *bkg = new RooUniform("bkg", "background p.d.f.", *variable);
    return new RooAddPdf(name, name, RooArgList(*pdf, *bkg), RooArgList(*NSignalEvents, *NBkgdEvents));
};
template RooAddPdf *PdfFactory::AddBackground<RooGaussian>(const char *name,
                                                           RooRealVar *variable,
                                                           RooGaussian *pdf,
                                                           RooRealVar *NSignalEvents,
                                                           RooRealVar *NBkgdEvents);
// }
#endif