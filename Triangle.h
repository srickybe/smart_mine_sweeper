/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Triangle.h
 * Author: ricky
 *
 * Created on 2 août 2021, 18:06
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cassert>
#include <iosfwd>


namespace ngn {
    
    class Triangle {
    public:

        Triangle();
        Triangle(int unsigned index1, int unsigned index2, int unsigned index3);
        int unsigned const & getVertexIndex(int i) const;
        int unsigned const * pointerToIndices() const;
        int unsigned getNumberOfVertexIndices()const;

    private:
        int unsigned indices_[3];

        bool const valid(int unsigned index1, int unsigned index2, int unsigned index3) const {
            return index1 != index2 && index1 != index3 && index2 != index3;
        }
    };
    
    std::ostream & operator<<(std::ostream & out, Triangle const & triangle);
}

#endif /* TRIANGLE_H */
