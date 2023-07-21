#ifndef FACE_HPP
#define FACE_HPP

#include <iosfwd>

namespace ngn {

    class Face {
        friend std::ostream & operator<<(std::ostream & out, Face const & face);

    public:
        Face();
        int unsigned const * getIndices()const;
        int unsigned getNumberOfIndices()const;
        void addIndex(int unsigned index);
        void writeTo(std::ostream & out)const;

    private:
        int unsigned indices_[10];
        int unsigned n_vertices_;
    };

    std::ostream & operator<<(std::ostream & out, Face const & face);
}

#endif // FACE_HPP
