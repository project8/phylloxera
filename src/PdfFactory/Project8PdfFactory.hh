#include "TObject.h"
#include <iostream>

#include "RooAbsPdf.h"
#include "KrTest.hh"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooAbsReal.h"

class Project8PdfFactory : public TObject
{
  public:
    Project8PdfFactory() { std::cout << "Hello you!" << std::endl; };

    template <class PdfClass>
    PdfClass *createPdf(PdfClass object)
    {
        return new PdfClass(object);
    };

    // template <class PdfClass>
    // RooDataSet *createDataSet(PdfClass *Pdf, RooAbsReal *var, int NDataPoints) { return (RooAbsPdf *)Pdf->generate(var, NDataPoints); };
};
// template int PdfFactory::createInstance<int>(int object);
// template RooDataSet *PdfFactory::createDataSet<RooGaussian>(RooGaussian *Pdf, RooAbsReal *var, int NDataPoints);
