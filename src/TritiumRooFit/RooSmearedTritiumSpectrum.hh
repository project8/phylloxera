// //
// //  RooTritiumSpectrum.h
// //  TritiumSpectrum
// //
// //  Created by Guigue, Mathieu on 10/26/17.
// //

// #ifndef RooSmearedTritiumSpectrum_h
// #define RooSmearedTritiumSpectrum_h

// #include "RooFFTConvPdf.h"
// #include "RooRealVar.h"
// #include "RooGaussian.h"


// #include "RooSimpleTritiumSpectrum.hh"



// class RooSmearedTritiumSpectrum: public RooFFTConvPdf{
// public:
//     enum SmearingType { None, Gaussian, Cauchy };
//     RooSmearedTritiumSpectrum(const char *, const char *, RooRealVar& ,RooRealVar& , RooRealVar& , RooRealVar& , SmearingType ); // uses KE, Q, m_neutrino, width

// public:
//     RooFFTConvPdf getSpectrum() {return _smearedspectrum;}

// protected:
//     int _cache;
//     SmearingType _type;
//     RooSimpleTritiumSpectrum _spectrum;
//     RooGaussian _gaussian;
//     RooFFTConvPdf _smearedspectrum;


//     // RooRealProxy _KE;
//     // RooRealProxy _endpoint;
//     // RooRealProxy _neutrinomass;
//     // RooRealProxy _width;

// };
    

// #endif /* RooTritiumSpectrum_h */
