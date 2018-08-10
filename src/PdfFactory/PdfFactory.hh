#ifndef PDFFACTORY
#define PDFFACTORY

#include "TObject.h"
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
class PdfFactory : public TObject
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
    template <class PdfClass>
    RooFFTConvPdf *GetSelfConvolPdf(const char *, RooRealVar *, PdfClass *, int = 10000);
    template <class PdfClass>
    RooFFTConvPdf *GetMultiSelfConvolPdf(const char *, RooRealVar *, PdfClass *, int, int = 10000);

  protected:
    const char *fName;
    ClassDef(PdfFactory, 1)
};

// Smearing Pdf
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
                                                               int GetSelfConvolPdf);

// Background addition
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

// Self convolution
template <class PdfClass>
RooFFTConvPdf *PdfFactory::GetSelfConvolPdf(const char *name, RooRealVar *variable, PdfClass *pdf, int numberBinsCache)
{
    variable->setBins(numberBinsCache, "cache");

    PdfClass *clonePdf = new PdfClass(*pdf, "clone");
    return new RooFFTConvPdf(name, name, *variable, *pdf, *clonePdf);
};
template RooFFTConvPdf *PdfFactory::GetSelfConvolPdf<RooGaussian>(const char *name,
                                                                  RooRealVar *variable,
                                                                  RooGaussian *pdf,
                                                                  int GetSelfConvolPdf);

// Multi Self convolution
template <class PdfClass>
RooFFTConvPdf *PdfFactory::GetMultiSelfConvolPdf(const char *name, RooRealVar *variable, PdfClass *pdf, int NConvolutions, int numberBinsCache)
{
    RooFFTConvPdf **vTempPdf = new RooFFTConvPdf *[NConvolutions];
    vTempPdf[0] = GetSelfConvolPdf<PdfClass>("tempPdf", variable, pdf, numberBinsCache);
    vTempPdf[0]->Print();
    for (int iConv = 1; iConv < NConvolutions; iConv++)
    {
        vTempPdf[iConv] = new RooFFTConvPdf(name, name, *variable, *vTempPdf[iConv - 1], *pdf);
        vTempPdf[iConv]->Print();
    }
    return vTempPdf[NConvolutions - 1];
};
template RooFFTConvPdf *PdfFactory::GetMultiSelfConvolPdf<RooGaussian>(const char *name,
                                                                       RooRealVar *variable,
                                                                       RooGaussian *pdf,
                                                                       int GetSelfConvolPdf,
                                                                       int NConvolutions);

// }
#endif