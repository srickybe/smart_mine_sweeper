/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Polygon.h
 * Author: ricky
 *
 * Created on 2 août 2021, 18:24
 */

#ifndef POLYGON_H
#define POLYGON_H

#include <boost/shared_array.hpp>
#include <cassert>
#include <iosfwd>


namespace ngn {
    
    class Polygon {
    public:

        Polygon();
        Polygon(int unsigned const indices[], int unsigned N);
        
        int unsigned const & getVertexIndex(int i)const;
        int unsigned const * pointerToIndices()const;
        int unsigned getNumberOfVertexIndices()const;

    private:
        boost::shared_array< int unsigned > indices_;
        int unsigned n_indices_;

        bool valid(int unsigned const indices[], int unsigned N)const;
    };
    
    std::ostream & operator<<(std::ostream & out, Polygon const & polygon);
}

#endif /* POLYGON_H */
