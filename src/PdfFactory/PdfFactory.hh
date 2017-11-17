#ifndef PDFFACTORY
#define PDFFACTORY

#include "TObject.h"
#include <iostream>

#include "RooGaussian.h"
#include "RooRealVar.h"
#include "RooFFTConvPdf.h"

namespace Phylloxera
{
class PdfFactory : public TObject
{
  public:
    PdfFactory() { std::cout << "Hello you!" << std::endl; };

    template <class PdfClass>
    PdfClass *createPdf(PdfClass object)
    {
        return new PdfClass(object);
    };

    template <class PdfClass>
    RooFFTConvPdf *GetSmearedPdf(const char *, const char *, RooRealVar *, PdfClass *, RooRealVar *, int = 10000);
};
}
#endif