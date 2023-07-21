#ifndef VTN_HPP
#define VTN_HPP

#include <iosfwd>

namespace ngn {

    struct VTN {
        int point_index;
        int texture_index;
        int normal_index;

        VTN();
		VTN(int point_index, int texture_index, int normal_index);
		bool const operator<(VTN const & vtn)const;
    };

    std::ostream & operator<<(std::ostream & out, VTN const & vtn);
}

#endif // VTN_HPP