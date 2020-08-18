//Andrew Qin
//132244195
//aqin1@myseneca.ca

#ifndef SDDS_VEHICLE_H
#define SDDS_VEHICLE_H
#include <iostream>
#include "ReadWritable.h"

namespace sdds {
	const int LicensePlateLength = 8;
	class Vehicle : public ReadWritable {
		char LicensePlate[LicensePlateLength];
		char* MakeModel;
		int ParkingNumber;
	public:
		Vehicle();
		Vehicle(const char* Plate, const char* Model);
		virtual~Vehicle();
		int getParkingSpot();
		void setParkingSpot(int number);
		
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout)const;
		Vehicle(const Vehicle& source) = delete;
		Vehicle& operator=(const Vehicle& source) = delete;
		bool operator==(const char*) const;
		bool operator==(const Vehicle& vehicle1) const;

	protected:
		void setEmpty();
		bool isEmpty();
		const char* getLicensePlate()const;
		char* getMakeModel() const;
		void setMakeModel(const char*);

	};

	
	





}








#endif