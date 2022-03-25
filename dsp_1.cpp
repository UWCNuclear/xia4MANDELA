//
//**********************************************************************************
//**********************************************************************************
//********  Calculation for the Digital Signal Processing (DSP) parameters *********
//********  Author: Dr. Kushal Kapoor **********************************************
//********  Last modified -03/09/2019 **********************************************
//**********************************************************************************
//

//libraries to be used according to the requirements {interfacing with ROOT at later stage!!!}
#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <stdlib.h>


using namespace std;

//
//Class Energy Resolution calculates the energy resolution of the given detector. 
//Information required: Peak Full Width at Half Maximum (FWHM) & Sigma 
//For details Read: K. Kapoor et. al., Modern African Nuclear Detector laboratory, HYPERFINE, GOA 2019
//

class EnergyResolution {
	private:
		string Detector;
		double FWHM, Sigma, Resolution;
	public:
		void setter(void) {
			std::cout << "Type of detector: \t";
			cin >> Detector;
			std::cout << "FWHM: \t";
			cin >> FWHM;
			std::cout << "Sigma: \t";
			cin >> Sigma;
			Resolution = FWHM / Sigma;
			std::cout << "The " << Detector << " Energy resolution is " << Resolution <<endl;
		}
	string getDetector() { return Detector; }
	double getResolution() { return Resolution; }
};

//
//Class Parameters calculates the average values for the parameters for given detector. 
//Information required: Pulse Risetime & Decay 
//For details Read: K. Kapoor et. al., Modern African Nuclear Detector laboratory, HYPERFINE, GOA 2019
//

class Parameters {
	private:
		double energyRisetime, tau, traceLength, traceDelay, triggerFlattop, triggerRisetime, energyFlattop, TAU;
	public:
		void setter(void) {
			std::cout << "Energy Risetime (us): \t";
			cin >> energyRisetime;
			std::cout << "Decay Time (us): \t\t";
			cin >> tau;
			energyFlattop = energyRisetime/3.99;
			traceLength = (1.5 * energyRisetime) + energyFlattop;
			traceDelay = 0.25 * traceLength;
			triggerFlattop = 0.24 * energyRisetime;
			triggerRisetime = 0.23 * energyRisetime;
			TAU = 1.1 * tau;

			std::cout << "\n Calculated parameter in (us): \t" <<endl;
			std::cout << "\n Slow filter parameter (Energy Filter):---- \t" ;
			std::cout << "\n Energy Risetime: \t" << energyRisetime;
			std::cout << "\n Energy Flattop: \t" << energyFlattop  <<endl;
			std::cout << "\n Fast filter parameter (Timing Filter):--- \t" ;
			std::cout << "\n Trigger Risetime: \t" << triggerRisetime;
			std::cout << "\n Trigger Flattop: \t" << triggerFlattop <<endl;
			std::cout << "\n Trace parameters :---- \t" ;
			std::cout << "\n Trace Length: \t\t" << traceLength;
			std::cout << "\n Trace Delay: \t\t" << traceDelay;
			std::cout << "\n Tau: \t\t\t" << TAU <<endl;


		}
		double getEnergyRisetime() { return energyRisetime; }
		double getEnergyFlattop() { return energyFlattop; }
		double getTraceLength() { return traceLength; }
		double getTraceDelay() { return traceDelay; }
		double getTau() { return tau; }
		double getTriggerRisetime() { return triggerRisetime; }
		double getTriggerFlattop() { return triggerFlattop; }
};

class semicon {
	private:
		double ER, t, tL, tD, tF, tR, eF, TU, eR;
	public:
		void setter(void) {

			std::cout << "Energy Risetime (us): \t";
			cin >> eR;
			std::cout << "Decay Time (us): \t\t";
			cin >> t;
			eF = eR/4.2;
			tL = (1.3 * eR) + eF;
			tD = 0.267 * tL;
			tF = 0.201 * eR;
			tR = 0.206 * eR;
			TU = 1.19* t;

			std::cout << "\n Calculated parameter in (us): \t" <<endl;
			std::cout << "\n Slow filter parameter (Energy Filter):---- \t" ;
			std::cout << "\n Energy Risetime: \t" << eR;
			std::cout << "\n Energy Flattop: \t" << eF  <<endl;
			std::cout << "\n Fast filter parameter (Timing Filter):--- \t" ;
			std::cout << "\n Trigger Risetime: \t" << tR;
			std::cout << "\n Trigger Flattop: \t" << tF <<endl;
			std::cout << "\n Trace parameters :---- \t" ;
			std::cout << "\n Trace Length: \t\t" << tL;
			std::cout << "\n Trace Delay: \t\t" << tD;
			std::cout << "\n Tau: \t\t\t" << TU <<endl;
		}
		double getEnergyRisetime() { return eR; }
		double getEnergyFlattop() { return eF; }
		double getTraceLength() { return tL; }
		double getTraceDelay() { return tD; }
		double getTau() { return t; }
		double getTriggerRisetime() { return tR; }
		double getTriggerFlattop() { return tF; }
	   };

int main()
{
	int option;
	std::cout << "Options:\n1: Detector Energy Resolution\n2: Digital System Parameters for scintillator detector:\n3: Digital System Parameters for Semiconductor detector:\n";
	cin >> option;
	if (option == 1)
	{
		EnergyResolution ER;
		ER.setter();
	}
	if (option == 2)
	{
		Parameters P;
		P.setter();
	}
	if (option == 3)
	{
		semicon SD;
		SD.setter();
	}
}



// VB- Windows machine
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu 


   
