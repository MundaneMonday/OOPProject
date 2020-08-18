#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Car.h"
#include <cctype>
using namespace sdds;

namespace sdds {
	Car::Car() {
		carwash = false;
	};

	Car::Car(const char* Plate, const char* Model) : Vehicle(Plate, Model) {
		carwash = false;
	};
	std::istream& Car::read(std::istream& istr) {
		char response[10];
		for (int i = 0; i < 10; i++) {
			response[i] = '\0';
		}
		if (isCsv()) {

			Vehicle::read(istr);
			istr >> carwash;
			istr.clear();
			istr.ignore(256, '\n');

		}
		else {
			std::cout << std::endl;
			std::cout << "Car Information Entry" << std::endl;
			Vehicle::read(istr);
			std::cout << "Carwash while parked? (Y)es/(N)o: ";
			istr >> response;
			istr.clear();
			istr.ignore(1000, '\n');
			while (response[1] != '\0' || (response[0] != 'y' && response[0] != 'Y' && response[0] != 'n' && response[0] != 'N')) {
				std::cout << "invalid Response, only (Y)es or (N)o are acceptable, retry: ";
				istr >> response;
				istr.clear();
				istr.ignore(1000, '\n');
			}
			
			if (response[0] == 'y' || response[0] == 'Y') {
				carwash = true;
			}
			else if (response[0] == 'n' || response[0] == 'N') {
				carwash = false;
			}
			else {
				carwash = false;
			}
			

		}
		return istr;
	};
	std::ostream& Car::write(std::ostream& ostr)const {
		
		if (*getLicensePlate()== '\0'|| getMakeModel()==nullptr) {
			ostr << "Invalid Car Object" << std::endl;
			
		}
		else {
			if (isCsv()) {
				ostr << "C,";

			}
			else {
				ostr << "Vehicle type: Car" << std::endl;
				
			}
			Vehicle::write(ostr);
			if (isCsv()) {
				ostr << carwash << std::endl;
			}
			else {
				if (carwash == true) {
					ostr << "With Carwash" << std::endl;

				}
				else if (carwash == false) {
					ostr << "Without Carwash" << std::endl;
				}

			}

		}
			
		return ostr;
	};






}