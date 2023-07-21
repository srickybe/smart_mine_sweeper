#include "VTN.h"
#include <iostream>

namespace ngn {
	
	VTN::VTN() {
	}

	VTN::VTN(int point_index, int texture_index, int normal_index)
	: point_index(point_index),
	texture_index(texture_index),
	normal_index(normal_index) {
	}

	bool const VTN::operator<(VTN const & vtn)const {
		if (point_index < vtn.point_index) {
			return true;
		}

		if (texture_index < vtn.texture_index) {
			return true;
		}

		if (normal_index < vtn.normal_index) {
			return true;
		}

		return false;
	}
	
    std::ostream & operator<<(std::ostream & out, VTN const & vtn) {
        std::cout << vtn.point_index << "/" << vtn.texture_index << "/";
        std::cout << vtn.normal_index << "\n";

        return out;
    }
}