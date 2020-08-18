//Andrew Qin
//132244195
//aqin1@myseneca.ca

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Vehicle.h"
#include <string.h>
#include<cctype>

using namespace sdds;

namespace sdds {
	Vehicle::Vehicle() {
		for (int i = 0; i < LicensePlateLength; i++) {
			LicensePlate[i] = '\0';
		}
		MakeModel = nullptr;
		ParkingNumber = 0;
		LicensePlate[0] = '\0';
	};
	Vehicle::Vehicle(const char* Plate, const char* Model) {
		for (int i = 0; i < LicensePlateLength; i++) {
			LicensePlate[i] = '\0';
		}
		ParkingNumber = 0;
		LicensePlate[0] = '\0';
		MakeModel = nullptr;


		if (Plate != nullptr && Plate[0] != '\0' && Model != nullptr && strlen(Plate) <= LicensePlateLength && strlen(Plate) >= 1 && Model[0] != '\0' && strlen(Model) >= 2 && strlen(Model) <= 60) {



			strcpy(LicensePlate, Plate);
			setMakeModel(Model);
		}
		else {
			setEmpty();
		}
	};
	Vehicle::~Vehicle() {
		if (MakeModel != nullptr) {
			delete[] MakeModel;
		}
	};

	void Vehicle::setEmpty() {
		if (MakeModel != nullptr) {
			delete[] MakeModel;
		}
		for (int i = 0; i < LicensePlateLength; i++) {
			LicensePlate[i] = '\0';
		}
		LicensePlate[0] = '\0';
		MakeModel = nullptr;
		ParkingNumber = 0;
	};
	bool Vehicle::isEmpty() {
		if (LicensePlate[0] == '\0' && MakeModel == nullptr && ParkingNumber == 0) {
			return true;
		}
		else {
			return false;
		}
	};
	const char* Vehicle::getLicensePlate() const{
		return LicensePlate;
	};
	char* Vehicle::getMakeModel() const {
		return MakeModel;
	};
	void Vehicle::setMakeModel(const char* model) {
		if (MakeModel != nullptr) {
			delete[] MakeModel;
		}

		if (model == nullptr || model[0] == '\0') {
			setEmpty();

		}
		else {
			MakeModel = new char[strlen(model) + 1];
			strcpy(MakeModel, model);
		}

	};


	int Vehicle::getParkingSpot() {
		return ParkingNumber;
	};
	void Vehicle::setParkingSpot(int number) {
		if (number < 0) {
			setEmpty();
		}
		else {
			ParkingNumber = number;
		}
	};
	bool Vehicle::operator==(const char* Plate) const {
		int PlateLength1 = strlen(Plate);
		int PlateLength2 = strlen(LicensePlate);


		if (PlateLength1 == PlateLength2) {
			for (int i = 0; i < PlateLength1; i++) {
				if (toupper(LicensePlate[i]) != toupper(Plate[i])) {
					return false;
				}
			}
			return true;
		}
		else {

			return false;
		}

	};
	bool Vehicle::operator==(const Vehicle& vehicle1) const {
		int PlateLength1 = strlen(vehicle1.LicensePlate);
		int PlateLength2 = strlen(LicensePlate);


		if (PlateLength1 == PlateLength2) {
			for (int i = 0; i < PlateLength1; i++) {
				if (toupper(LicensePlate[i]) != toupper(vehicle1.LicensePlate[i])) {
					return false;
				}
			}
			return true;
		}
		else {

			return false;
		}

	};

	std::istream& Vehicle::read(std::istream& istr) {

		if (isCsv()) {
			istr >> ParkingNumber;
			istr.ignore(1);

			istr.getline(LicensePlate, LicensePlateLength, ',');
			if (MakeModel != nullptr) {
				delete[] MakeModel;
			}

			MakeModel = new char[60];
			istr.getline(MakeModel, 60, ',');




			for (int i = 0; i < LicensePlateLength; i++) {
				if (isalpha(LicensePlate[i])) {
					LicensePlate[i] = toupper(LicensePlate[i]);
				}

			}



		}
		else {
			std::cout << "Enter License Plate Number: ";
			istr >> LicensePlate;
			istr.clear();
			istr.ignore(1000, '\n');

			while (strlen(LicensePlate) > LicensePlateLength) {

				std::cout << "Invalid Licence Plate, try again: ";
				istr >> LicensePlate;
				istr.clear();
				istr.ignore(1000, '\n');

			}


			for (int i = 0; i < LicensePlateLength; i++) {
				if (isalpha(LicensePlate[i])) {
					LicensePlate[i] = toupper(LicensePlate[i]);
				}
			}

			std::cout << "Enter Make and Model: ";
			if (MakeModel != nullptr) {
				delete[] MakeModel;
			}
			MakeModel = new char[60];
			istr.getline(MakeModel, 60, '\n');


			while (strlen(MakeModel) < 2 || strlen(MakeModel) > 60) {

				std::cout << "Invalid Make and model, try again: ";
				istr.getline(MakeModel, 60, '\n');
			}


		}

		if (istr.fail()) {
			setEmpty();
		}



		return istr;
	};
	std::ostream& Vehicle::write(std::ostream& ostr) const {
		if (LicensePlate[0] == '\0' || MakeModel == nullptr) {
			ostr << "Invalid Vehicle Object" << std::endl;
		}
		else {
			if (isCsv()) {
				ostr << ParkingNumber << ',' << LicensePlate << ',' << MakeModel << ',';
			}
			else {
				ostr << "Parking Spot Number: ";
				if (ParkingNumber != 0) {
					ostr << ParkingNumber;
				}
				else {
					ostr << "N/A";
				}
				ostr << std::endl;
				ostr << "License Plate: " << LicensePlate << std::endl;
				ostr << "Make and Model: " << MakeModel << std::endl;

			}

		}


		return ostr;

	};






}