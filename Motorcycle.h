#ifndef SDDS_MOTORCYCLE_H
#define SDDS_MOTORCYCLE_H
#include <iostream>
#include "Vehicle.h"
namespace sdds {
	class Motorcycle : public Vehicle {
	private:
		bool sidecar;
	public:
		Motorcycle();
		Motorcycle(const char* license, const char* makemodel);
		Motorcycle(const Motorcycle& source) = delete;
		Motorcycle& operator=(const Motorcycle& source) = delete;
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout)const;




	};

















}
#endif