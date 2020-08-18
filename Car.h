#ifndef SDDS_CAR_H
#define SDDS_CAR_H
#include <iostream>
#include "Vehicle.h"
namespace sdds {
	class Car : public Vehicle {
	private:
		bool carwash;
	public:
		Car();
		Car(const char* license, const char* makemodel);
		Car(const Car& source) = delete;
		Car& operator=(const Car& source) = delete;
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout)const;

	};

















}
#endif