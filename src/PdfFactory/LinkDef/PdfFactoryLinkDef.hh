#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedefs;

#pragma link C++ namespace Phylloxera;

#pragma link C++ class Phylloxera::PdfFactory + ;

#pragma link C++ function Phylloxera::PdfFactory::GetSmearedPdf;
#pragma link C++ function Phylloxera::PdfFactory::AddBackground;

#pragma link C++ enum Phylloxera::PdfFactory::SmearingType;

#endif