#ifndef PDFFACTORY
#define PDFFACTORY

#include "TObject.h"
#include <iostream>
// #include "logger.hh"

#include "RooGaussian.h"
#include "RooRealVar.h"
#include "RooFFTConvPdf.h"
#include "RooAddPdf.h"
#include "RooEffProd.h"
#include "RooFormulaVar.h"
#include "TMath.h"

#include "RooBreitWigner.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooUniform.h"

// LOGGER(pdffactory, "PdfFactory");

// namespace Phylloxera
// {
class PdfFactory: public TObject
{
  public:
    enum SmearingType
    {
        Cauchy,
        Lorentzian,
        Gaussian
    };
    enum BackgroundShape
	{
    	Uniform,
		NonUniform
	};
    PdfFactory(){};
    PdfFactory(const char *name) : fName(name){};
    inline virtual ~PdfFactory() = default;

    template <class PdfClass>
    RooFFTConvPdf *GetSmearedPdf(const char *, SmearingType, RooRealVar *, PdfClass *, RooRealVar *, RooRealVar *, int = 10000);
    template <class PdfClass>
    RooAddPdf *AddBackground(const char *, BackgroundShape, RooRealVar *, PdfClass *, RooRealVar *, RooRealVar *, RooArgList *);
    template <class PdfClass>
    RooEffProd *MultiplyPolynom(const char *, const char *, RooArgList *, PdfClass *);

    //template <class PdfClass>
    //RooAbsPdf *CopyPdf(const char *, PdfClass * );


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
RooAddPdf *PdfFactory::AddBackground(const char *name, BackgroundShape shape, RooRealVar *variable, PdfClass *pdf, RooRealVar *NSignalEvents, RooRealVar *NBkgdEvents, RooArgList *pars)
{
	RooUniform *bkg = new RooUniform("bkg", "background p.d.f.", *variable);
	switch( shape )
	{
	case Uniform:
		return new RooAddPdf(name, name, RooArgList(*pdf, *bkg), RooArgList(*NSignalEvents, *NBkgdEvents));
	case NonUniform:
		RooEffProd *bkg1 = PdfFactory::MultiplyPolynom<RooUniform>("pb", "bkg1", pars, bkg);
		return new RooAddPdf(name, name, RooArgList(*pdf, *bkg1), RooArgList(*NSignalEvents, *NBkgdEvents));
	};
	return 0;

};
template RooAddPdf *PdfFactory::AddBackground<RooGaussian>(const char *name,
                                                           BackgroundShape shape,
                                                           RooRealVar *variable,
                                                           RooGaussian *pdf,
                                                           RooRealVar *NSignalEvents,
                                                           RooRealVar *NBkgdEvents,
														   RooArgList *pars);

template <class PdfClass>
RooEffProd *PdfFactory::MultiplyPolynom(const char *poly_name, const char *name, RooArgList *pars, PdfClass *pdf)
{
	//RooPolynomial *poly = new RooPolynomial("poly", "polynomial p.d.f.", *variable, *pars, lowestOrder);
	RooFormulaVar *poly = new RooFormulaVar(poly_name, "@1+@2*TMath::Power(@0,1)+@3*TMath::Power(@0,2)+@4*TMath::Power(@0,3)+@5*TMath::Power(@0,4)", *pars);
	poly->Print();
	//RooEffProd *multipliedSpectrum = new RooEffProd(name, name, *pdf, poly);
	//multipliedSpectrum->Print();
    return new RooEffProd(name, name, *pdf, *poly);
};
template RooEffProd *PdfFactory::MultiplyPolynom<RooAbsPdf>(const char *poly_name,
                                                            const char *name,
															RooArgList *pars,
                                                            RooAbsPdf *pdf);

// }
#endif
