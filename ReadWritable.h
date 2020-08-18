#ifndef SDDS_READWRITABLE_H
#define SDDS_READWRITABLE_H
#include <iostream>

namespace sdds {
	class ReadWritable {
		bool comma;
	public:
		ReadWritable();
		bool isCsv()const;
		void setCsv(bool value);
		virtual ~ReadWritable() {};
		virtual std::ostream& write(std::ostream& ostr = std::cout)const = 0;
		virtual std::istream& read(std::istream& istr = std::cin) = 0;
		
		
	};

	std::ostream& operator<< ( std::ostream& is, ReadWritable& write );
	std::istream& operator>> ( std::istream& os, ReadWritable& read );



}




#endif