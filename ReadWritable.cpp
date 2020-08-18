#include <iostream>
#include "ReadWritable.h"
using namespace sdds;

namespace sdds {
	ReadWritable::ReadWritable() {
		comma = false;
	};
	
	bool ReadWritable::isCsv()const {
		return comma;
	};
	void ReadWritable::setCsv(bool value) {
		comma = value;
	};
	std::ostream& operator<<( std::ostream& is, ReadWritable& write) {
		
		return write.write(is);
	};
	std::istream& operator>>( std::istream& os, ReadWritable& read ) {
		return read.read(os);
	};


}
