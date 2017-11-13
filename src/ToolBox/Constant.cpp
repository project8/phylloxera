#include "TMath.h"

inline double ElectronMassIneV() { return 510998.910; }           // Electron mass in eV
inline double ElectronMassInKilogram() { return 9.10938356e-31; } // Electron mass in kilogram
inline double ElectronCharge() { return -1.6021766208e-19; }      // Electron charge in Coulomb
inline double PlanckConstant() { return 6.582119514e-16; }        // Reduced Planck's constant in eV*s
inline double LightSpeed() { return 299792458.; }                 // Speed of light in m/s
// inline double HBarC() { return hbar() * c(); }                                                // hbar * c
inline double AngularGyromagneticRatio() { return 1.758820088e+11; }                          // Angular gyromagnetic ratio in rad Hz/Tesla
inline double GyromagneticRatio() { return AngularGyromagneticRatio() / (2. * TMath::Pi()); } // Gyromagnetic ratio in Hz/Tesla
inline double BoltzmanConstant() { return 8.61733238e-5; }                                    // Boltzmann's constant in eV/Kelvin
inline double UnitMassIneV() { return 931.494061e6; }                                         // Unit mass in eV
inline double NumberOfSecondsPerYear() { return 365.25 * 86400.; }                            // Number of seconds per year
inline double FineStructureConstant() { return 0.0072973525664; }                             // fine structure constant

inline double eVInJoule() { return 1.602176565e-19; }  // conversion of one eV in Joule
inline double eVInKilogram() { return 1.782662 - 36; } // conversion of one eV in kilogram
// double PhaseVelocity(){return ;}
