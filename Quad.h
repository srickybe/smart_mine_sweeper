/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Quad.h
 * Author: ricky
 *
 * Created on 2 août 2021, 18:20
 */

#ifndef QUAD_H
#define QUAD_H

#include <cassert>
#include <iosfwd>


namespace ngn {

    class Quad {
    public:

        Quad();
        Quad(int unsigned index1, int unsigned index2, int unsigned index3, int unsigned index4);

        int unsigned const & getVertexIndex(int i) const;
        int unsigned const * pointerToIndices() const;
        int unsigned getNumberOfVertexIndices()const;

    private:
        int unsigned indices_[4];

        bool valid(int unsigned indices[], int n_indices)const;
    };

    std::ostream & operator<<(std::ostream & out, Quad const & quad);
}

#endif /* QUAD_H */
