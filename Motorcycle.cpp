#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Motorcycle.h"
#include <cctype>
using namespace sdds;

namespace sdds {
	Motorcycle::Motorcycle() {
		sidecar = false;
	};
	Motorcycle::Motorcycle(const char* license, const char* makemodel) : Vehicle(license, makemodel) {
		sidecar = false;
	};
	std::istream& Motorcycle::read(std::istream& istr) {
		char response[10];
		for (int i = 0; i < 10; i++) {
			response[i] = '\0';
		}
		if (isCsv()) {
			Vehicle::read(istr);
			istr >> sidecar;
			istr.ignore(256, '\n');
		}
		else {
			std::cout << std::endl;
			std::cout << "Motorcycle information entry" << std::endl;
			Vehicle::read(istr);
			std::cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			istr >> response;
			istr.clear();
			istr.ignore(1000, '\n');
			while (response[1] != '\0' || (response[0] != 'y' && response[0] != 'Y' && response[0] != 'n' && response[0] != 'N')) {
				std::cout << "invalid response, only (Y)es or (N)o are acceptable, retry: ";
				istr >> response;
				istr.clear();
				istr.ignore(1000, '\n');
			}
			if (response[0] == 'y' || response[0] == 'Y') {
				sidecar = true;
			}
			else if (response[0] == 'n' || response[0] == 'N') {
				sidecar = false;
			}
			else {
				sidecar = false;
			}
		}
		return istr;
	};
	std::ostream& Motorcycle::write(std::ostream& ostr)const {
		if (*getLicensePlate()== '\0'|| getMakeModel()==nullptr) {
			ostr << "Invalid Motocycle Object" << std::endl;

		}
		else {
			if (isCsv()) {
				ostr << "M,";
			}
			else {
				ostr << "Vehicle type: Motorcycle" << std::endl;
				
			}
			Vehicle::write(ostr);
			if (isCsv()) {
				ostr << sidecar << std::endl;
			}
			else {
				if (sidecar == true) {
					ostr << "With Sidecar" << std::endl;
				}
			}

		}
		return ostr;
	};





}