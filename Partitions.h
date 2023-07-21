#ifndef PARTITIONS_H
#define PARTITIONS_H

#include <iostream>

namespace ngn {
	
	class Partitions {
	public:
		Partitions(int i, int j, int k) : ints({i, j, k}) {}
		
		int getXAxisPartitions() const { return ints[0]; }
		int getYAxisPartitions() const { return ints[1]; }
		int getZAxisPartitions() const { return ints[2]; }
		int getAxisPartitions(int i) const { return ints[i]; }
		std::ostream & print(std::ostream & out) const { 
			out << "Partitions{" << getXAxisPartitions();
			out << ", " << getYAxisPartitions(); 
			out << ", " << getZAxisPartitions();
			out << "}"; 
			
			return out;
		}
		
	private:
		std::array<int, 3> ints;
	};
}
	
#endif // PARTITIONS_H