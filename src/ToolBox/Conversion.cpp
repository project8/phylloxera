#include "TMath.h"
#include "Constant.cpp"

inline double GetKineticEnergyFromFrequency(double frequency, double B)
//Return kinetic energy in eV
{
	double gamma = GyromagneticRatio() / frequency * B;
	return (gamma - 1.) * ElectronMassIneV();
}

inline double GetFrequencyFromKineticEnergy(double kineticEnergy, double B)
{
	double gamma = 1. + kineticEnergy / ElectronMassIneV();
	return GyromagneticRatio() / gamma * B;
}