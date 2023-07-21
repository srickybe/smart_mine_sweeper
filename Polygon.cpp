#include <iostream>
#include "Polygon.h"

namespace ngn {

    Polygon::Polygon()
    : indices_(),
    n_indices_(0) {
    }

    Polygon::Polygon(int unsigned const indices[], int unsigned N) {
        assert(N > 4);
        assert(valid(indices, N));

        n_indices_ = N;
        indices_ = boost::shared_array< int unsigned >(new int unsigned[ n_indices_ ]);

        for (int unsigned i = 0; i < n_indices_; ++i) {
            indices_[i] = indices[i];
        }
    }

    int unsigned const & Polygon::getVertexIndex(int i)const {
        assert(static_cast<int unsigned> (i) < n_indices_);

        return indices_[i];
    }

    int unsigned const * Polygon::pointerToIndices() const {
        return &indices_[0];
    }

    int unsigned Polygon::getNumberOfVertexIndices()const {
        return n_indices_;
    }


    bool Polygon::valid(int unsigned const indices[], int unsigned N)const {
        for (int unsigned i = 0; i < N; ++i) {
            for (int unsigned j = i + 1; j < N; ++j) {
                if (indices[i] == indices[j]) {
                    return false;
                }
            }
        }

        return true;
    }

    std::ostream & operator<<(std::ostream & out, Polygon const & polygon) {
        out << "[" << polygon.getVertexIndex(0);

        for (int unsigned i = 1; i < polygon.getNumberOfVertexIndices(); ++i) {
            out << ", " << polygon.getVertexIndex(i);
        }

        out << "]";

        return out;
    }
}
