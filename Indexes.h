#ifndef INDEXES_H
#define INDEXES_H

#include <array>
#include <iostream>

namespace ngn {
	class Indexes {
	public:
		Indexes(int i, int j, int k) : ints({i, j, k}) {}
		
		int getI() const { return ints[0]; }
		int getJ() const { return ints[1]; }
		int getK() const { return ints[2]; }
		int get(int i) const { return ints[i]; }
		
		std::ostream & print(std::ostream & out) const { 
			out << "(" << getI();
			out << ", " << getJ(); 
			out << ", " << getK();
			out << ")"; 
			
			return out;
		}
		
	private:
		std::array<int, 3> ints;
	};
	
	std::ostream & operator <<(std::ostream & out, Indexes const & indexes);
}

#endif // INDEXES_H