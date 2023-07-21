#include <iostream>
#include "Line.h"

namespace ngn {

    Line::Line() {
    }

    Line::Line(int unsigned index1, int unsigned index2) {
        indices_[0] = index1;
        indices_[1] = index2;
    }

    int unsigned const & Line::getVertexIndex(int i) const {
        assert(static_cast<int> (i) < 2);

        return indices_[i];
    }

    int unsigned const * Line::pointerToIndices() const {
        return &indices_[0];
    }

    int unsigned Line::getNumberOfVertexIndices()const {
        return 2;
    }

    bool Line::valid(int unsigned index1, int unsigned index2) const {
        return index1 != index2;
    }

    std::ostream & operator<<(std::ostream & out, Line const & line) {
        out << "[" << line.getVertexIndex(0);

        for (int unsigned i = 1; i < line.getNumberOfVertexIndices(); ++i) {
            out << ", " << line.getVertexIndex(i);
        }

        out << "]";

        return out;
    }
}
