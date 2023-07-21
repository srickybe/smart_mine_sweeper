#include <iostream>
#include "Quad.h"

namespace ngn {

    Quad::Quad() {
    }

    Quad::Quad(int unsigned index1, int unsigned index2, int unsigned index3, int unsigned index4) {
        indices_[0] = index1;
        indices_[1] = index2;
        indices_[2] = index3;
        indices_[3] = index4;

        assert(valid(indices_, 4));
    }

    bool Quad::valid(int unsigned indices[], int n_indices) const {
        assert(indices != 0);
        assert(n_indices == 4);

        for (int i = 0; i < 4; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                if (indices[i] == indices[j]) {
                    return false;
                }
            }
        }

        return true;
    }
        
    int unsigned const & Quad::getVertexIndex(int i) const {
        assert(static_cast<int> (i) < 4);

        return indices_[i];
    }

    int unsigned const * Quad::pointerToIndices() const {
        return &indices_[0];
    }

    int unsigned Quad::getNumberOfVertexIndices()const {
        return 4;
    }

    std::ostream & operator<<(std::ostream & out, Quad const & quad) {
        out << "[" << quad.getVertexIndex(0);

        for (int unsigned i = 1; i < quad.getNumberOfVertexIndices(); ++i) {
            out << ", " << quad.getVertexIndex(i);
        }

        out << "]";

        return out;
    }
}
