#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedefs;

// #pragma link C++ namespace Phylloxera;

#pragma link C++ class PdfFactory + ;

#pragma link C++ function PdfFactory::GetSmearedPdf;
#pragma link C++ function PdfFactory::AddBackground;
#pragma link C++ function PdfFactory::GetSelfConvPdf;
#pragma link C++ function PdfFactory::GetMultiSelfConvPdf;

#pragma link C++ enum PdfFactory::SmearingType;

#endif