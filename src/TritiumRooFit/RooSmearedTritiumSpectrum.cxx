// //
// //  RooTritiumSpectrum.hh
// //  TritiumSpectrum
// //
// //  Created by Guigue, Mathieu on 10/26/17.
// //

// #include "RooSmearedTritiumSpectrum.hh"



// RooSmearedTritiumSpectrum::RooSmearedTritiumSpectrum(const char *name, const char *title, RooRealVar& KE, RooRealVar& endpoint, RooRealVar& neutrinoMass, RooRealVar& width, SmearingType type):
// // _endpoint("endpoint","endpoint",this,endpoint),
// // _neutrinomass("neutrinomass","neutrino mass",this,neutrinoMass),
// // _width("width","width",this,width),
// _type(type)
// {
//     KE.setBins(10000,"cache");
//     // _KE("KE","kinetic energy",this,KE);
//     RooSimpleTritiumSpectrum simpleTritumSpectrum("tritiumSpectrum", "TritiumSpectrum",KE,endpoint,neutrinoMass);
//     RooRealVar mean("mean","mean",0);
//     std::cout << "here" <<std::endl;
//     _gaussian = RooGaussian("gaussianSmearing", "gaussianSmearing",KE,mean,width);
//     // switch(type) {
//     //     case None:
//     //         break;
//     //     case Cauchy:
//     //         break;
//         // case Gaussian:
//             _smearedspectrum = RooFFTConvPdf(name,title, KE,simpleTritumSpectrum,_gaussian);
//             // break;
//     // }
//     _smearedspectrum.generate(KE,100);
//     std::cout << "here" <<std::endl;
    
// };
