#ifndef SDDS_PARKING_H
#define SDDS_PARKING_H
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Vehicle.h"
namespace sdds {
	const int MaximumParking = 100;
	class Parking {
		int m_noOfSpots;
		Vehicle* vehiclearray[MaximumParking];
		int noOfParked;
		char* ParkString;
		Menu* parkingMenu;
		Menu* vehicleMenu;

		

		bool isEmpty();
		void ParkingStatus();
		void ParkVehicle();
		void ReturnVehicle();
		void ListParked();
		bool CloseParking();
		bool ExitParking();
		bool LoadData();
		void SaveData();







	public:
		Parking();
		Parking(const char* datafile, int noOfSpots);
		~Parking();
		Parking(const Parking& source) = delete;
		Parking& operator =(const Parking& source) = delete;
		int run();




	};



}
#endif