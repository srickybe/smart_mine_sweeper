#include "Face.h"
#include <cassert>
#include <iostream>

namespace ngn {

    Face::Face()
    : n_vertices_(0) {
    }

    int unsigned const * Face::getIndices()const {
        return indices_;
    }

    int unsigned Face::getNumberOfIndices()const {
        return n_vertices_;
    }

    void Face::addIndex(int unsigned index) {
        assert(n_vertices_ < 10);

        indices_[n_vertices_] = index;
        ++n_vertices_;
    }

    void Face::writeTo(std::ostream & out)const {
        std::cout << "n_vertex = " << n_vertices_ << "\n";

        for (int unsigned i = 0; i < n_vertices_; ++i) {
            std::cout << "indices_[" << i << "] = " << indices_[i] << "\n";
        }
    }

    std::ostream & operator<<(std::ostream & out, Face const & face) {
        assert(face.n_vertices_ > 0);

        out << "(" << face.indices_[0];

        for (int unsigned i = 0; i < face.n_vertices_; ++i) {
            out << "," << face.indices_[i];
        }

        out << ")\n";

        return out;
    }
}
