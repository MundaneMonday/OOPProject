//Andrew Qin//
//132244195//
#define _CRT_SECURE_NO_WARNINGS
#include<fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Parking.h"
using namespace sdds;

namespace sdds {
	Parking::Parking() {
		ParkString = nullptr;
		parkingMenu = nullptr;
		vehicleMenu = nullptr;
		vehiclearray[0] = nullptr;
		for (int i = 0; i < MaximumParking; i++) {
			vehiclearray[i] = nullptr;
		}
		m_noOfSpots = 0;
		noOfParked = 0;
	};
	Parking::Parking(const char* DataTitle, int noOfSpots) {
		ParkString = nullptr;
		parkingMenu = nullptr;
		for (int i = 0; i < MaximumParking; i++) {
			vehiclearray[i] = nullptr;
		}
		vehicleMenu = nullptr;
		vehiclearray[0] = nullptr;
		m_noOfSpots = 0;
		noOfParked = 0;
		if (DataTitle != nullptr && DataTitle[0] != '\0' && noOfSpots < MaximumParking && 11 >= noOfSpots) {
			m_noOfSpots = noOfSpots;
			ParkString = new char[strlen(DataTitle) + 1];
			strcpy(ParkString, DataTitle);
			vehicleMenu = new Menu;
			parkingMenu = new Menu;
		}
		else {
			ParkString = nullptr;
			parkingMenu = nullptr;
			vehicleMenu = nullptr;
			vehiclearray[0] = nullptr;
			for (int i = 0; i < MaximumParking; i++) {
				vehiclearray[i] = nullptr;
			}
			m_noOfSpots = 0;
			noOfParked = 0;
		}

		if (LoadData()) {
			parkingMenu->SetIndent(0);
			parkingMenu->setInput("Parking Menu, select an action:");
			parkingMenu->add("Park Vehicle");
			parkingMenu->add("Return Vehicle");
			parkingMenu->add("List Parked Vehicles");
			parkingMenu->add("Close Parking (End of day)");
			parkingMenu->add("Exit Program");

			vehicleMenu->SetIndent(1);
			vehicleMenu->setInput("Select type of the vehicle:");
			vehicleMenu->add("Car");
			vehicleMenu->add("Motorcycle");
			vehicleMenu->add("Cancel");

		}
		else {
			std::cout << "Error in data file" << std::endl;

			if (vehicleMenu != nullptr) {
				delete vehicleMenu;
			}
			if (parkingMenu != nullptr) {
				delete parkingMenu;
			}
			if (ParkString != nullptr) {
				delete[] ParkString;
			};
			this->ParkString = nullptr;
			this->vehicleMenu = nullptr;
			this->parkingMenu = nullptr;
		}
	};
	Parking::~Parking() {
		SaveData();
		if (vehicleMenu != nullptr) {


			delete vehicleMenu;
		}
		if (parkingMenu != nullptr) {
			delete parkingMenu;
		}
		if (ParkString != nullptr) {
			delete[] ParkString;
		}
		for (int i = 0; i < m_noOfSpots; i++) {
			if (vehiclearray[i] != nullptr) {
				delete vehiclearray[i];
			}
		}

	}


	bool Parking::isEmpty() {
		if (ParkString == nullptr && parkingMenu == nullptr && vehicleMenu == nullptr) {
			return true;
		}
		else {
			return false;
		}

	};
	void Parking::ParkingStatus() {
		std::cout << "****** Seneca Valet Parking ******" << std::endl;
		std::cout << "*****  Available spots: " << std::left << std::setw(4) << m_noOfSpots - noOfParked << " *****" << std::endl;
	};
	void Parking::ParkVehicle() {
		int number = vehicleMenu->run();
		if (m_noOfSpots == noOfParked) {
			std::cout << "Parking is full" << std::endl;
		}
		else if (number == 1) {

			for (int i = 0; i < m_noOfSpots; i++) {
				if (vehiclearray[i] == nullptr) {
					vehiclearray[i] = new Car;
					vehiclearray[i]->setCsv(false);
					vehiclearray[i]->read();
					vehiclearray[i]->setParkingSpot(i + 1);
					std::cout << "Parking Ticket" << std::endl;
					vehiclearray[i]->write();
					noOfParked++;
					break;
				}
			}

		}
		else if (number == 2) {


			for (int i = 0; i < m_noOfSpots; i++) {
				if (vehiclearray[i] == nullptr) {
					vehiclearray[i] = new Motorcycle;
					vehiclearray[i]->setCsv(false);
					vehiclearray[i]->read();
					vehiclearray[i]->setParkingSpot(i + 1);
					std::cout << "Parking Ticket" << std::endl;
					vehiclearray[i]->write();
					noOfParked++;
					break;
				}
			}

		}
		else if (number == 3) {
			std::cout << "Parking Cancelled" << std::endl;
		}

	};
	void Parking::ReturnVehicle() {
		char LicensePlate1[100];
		for (int i = 0; i < LicensePlateLength; i++) {
			LicensePlate1[i] = '\0';
		}
		std::cout << "Return Vehicle" << std::endl;
		std::cout << "Enter License Plate Number: ";
		std::cin >> LicensePlate1;
		std::cin.clear();
		std::cin.ignore(1000, '\n');

		while (strlen(LicensePlate1) + 1 > LicensePlateLength || strlen(LicensePlate1) == 0) {

			std::cout << "Invalid Licence Plate, try again: ";
			std::cin >> LicensePlate1;
			std::cin.clear();
			std::cin.ignore(1000, '\n');


		}
		for (int i = 0; i < noOfParked; i++) {
			if (*vehiclearray[i] == LicensePlate1) {
				std::cout << "Returning: ";
				vehiclearray[i]->setCsv(false);
				vehiclearray[i]->write();
				delete vehiclearray[i];
				vehiclearray[i] = nullptr;
				noOfParked--;
				break;
			}
		}

	};
	void Parking::ListParked() {
		std::cout << "*** List of parked vehicles ***" << std::endl;
		for (int i = 0; i < noOfParked; i++) {
			if (vehiclearray[i] != nullptr) {
				vehiclearray[i]->setCsv(false);
				vehiclearray[i]->write();
				std::cout << "-------------------------------" << std::endl;
			}

		}
	};
	bool Parking::CloseParking() {
		if (noOfParked == 0) {
			std::cout << "Closing Parking" << std::endl;
			return true;
		}
		else {
			std::cout << "This will Remove and tow all remaining Vehicles from the Parking!" << std::endl;
			char response[10];
			for (int i = 0; i < 10; i++) {
				response[i] = '\0';
			}
			std::cout << "Are you sure? (Y)es/(N)o: ";
			std::cin >> response;
			std::cin.clear();
			std::cin.ignore(1000, '\n');

			while (response[1] != '\0' || (response[0] != 'y' && response[0] != 'Y' && response[0] != 'n' && response[0] != 'N')) {
				std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				std::cin >> response;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
			if (response[0] == 'y' || response[0] == 'Y') {
				std::cout << "Closing Parking" << std::endl;
				for (int i = 0; i < noOfParked; i++) {
					if(vehiclearray[i]!=nullptr){
					std::cout << "Towing request" << std::endl;
					std::cout << "*********************" << std::endl;
					vehiclearray[i]->setCsv(false);
					vehiclearray[i]->write();
					std::cout << std::endl;
					delete vehiclearray[i];
					vehiclearray[i] = nullptr;
}
				}

				return true;
			}
			else if (response[0] == 'n' || response[0] == 'N') {
				return false;
			}
			else {
				return false;
			}


		}
	};
	bool Parking::ExitParking() {
		char response[10];
		for (int i = 0; i < 10; i++) {
			response[i] = '\0';
		}
		std::cout << "This will terminate the program!" << std::endl;
		std::cout << "Are you sure? (Y)es/(N)o: ";

		std::cin >> response;
		std::cin.clear();
		std::cin.ignore(1000, '\n');

		while (response[1] != '\0' || (response[0] != 'y' && response[0] != 'Y' && response[0] != 'n' && response[0] != 'N')) {
			std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			std::cin >> response;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		if (response[0] == 'y' || response[0] == 'Y') {
			return true;
		}
		else if (response[0] == 'n' || response[0] == 'N') {
			return false;
		}
		else {
			return false;
		}
	};
	bool Parking::LoadData() {
		
		bool good = true;
		if (!(isEmpty())) {
			std::ifstream file(ParkString);

			if (file) {
				char c;
				Vehicle* temp;
				
				
				while (file.good() && noOfParked < m_noOfSpots) {
					

					file >> c;
					file.ignore(1);
					if (c == 'M') {
						temp = new Motorcycle;
					}
					else if (c == 'C') {
						temp = new Car;
					}
					if (c == 'M' || c == 'C') {
						temp->setCsv(true);
						temp->read(file);


						if (!(file.fail()) || !(file.bad())) {

							if (c == 'M') {
								vehiclearray[(temp->getParkingSpot())-1] = new Motorcycle;
							}
							else if (c == 'C') {
								vehiclearray[(temp->getParkingSpot()) - 1] = new Car;
							}

							vehiclearray[(temp->getParkingSpot()) - 1] = temp;
							
							
							noOfParked++;
							

						}
						else {

							delete temp;

							good = false;
							
						}
					}
					
				}
				
				
			}
			else {


			}


		}
		else {


		}
		
		return good;
	};
	void Parking::SaveData() {
		if (isEmpty()) {

		}
		else {
			std::ofstream file("ParkingData.csv");


			if (file) {
				for (int i = 0; i < noOfParked; i++) {
					if (vehiclearray[i] != nullptr) {
						vehiclearray[i]->setCsv(true);
						vehiclearray[i]->write(file);
					}
				}

			}


			std::cout << "Exiting program!" << std::endl;
			std::cout << "Saving data into " << ParkString << std::endl;

		}


	}
	int Parking::run() {
		if (ParkString == nullptr && parkingMenu == nullptr && vehicleMenu == nullptr) {
			return 1;
		}
		else {
			bool end = false;

			while (end == false) {

				ParkingStatus();
				int number = parkingMenu->run();
				if (number == 1) {
					ParkVehicle();
				}
				else if (number == 2) {
					ReturnVehicle();
				}
				else if (number == 3) {
					ListParked();
				}
				else if (number == 4) {
					if (CloseParking()) {
						end = true;
					}
					else {
						end = false;
					}

				}
				else if (number == 5) {
					if (ExitParking()) {
						end = true;
					}
					else {
						end = false;
					}
				}



			}




			return 0;

		}

	}

}