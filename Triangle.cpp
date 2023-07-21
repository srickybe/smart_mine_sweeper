#include <iostream>
#include "Triangle.h"

namespace ngn {

    Triangle::Triangle() {
    }

    Triangle::Triangle(int unsigned index1, int unsigned index2, int unsigned index3) {
        indices_[0] = index1;
        indices_[1] = index2;
        indices_[2] = index3;
    }

    int unsigned const & Triangle::getVertexIndex(int i) const {
        assert(static_cast<int> (i) < 3);

        return indices_[i];
    }

    int unsigned const * Triangle::pointerToIndices() const {
        return &indices_[0];
    }

    int unsigned Triangle::getNumberOfVertexIndices()const {
        return 3;
    }
    
    std::ostream & operator<<(std::ostream & out, Triangle const & triangle) {
        out << "[" << triangle.getVertexIndex(0);
        
        for (int unsigned i = 1; i < triangle.getNumberOfVertexIndices(); ++i) {
            out << ", " << triangle.getVertexIndex(i); 
        }
        
        out << "]";
        
        return out;
    }
}
