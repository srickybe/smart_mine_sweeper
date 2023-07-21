/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Line.h
 * Author: ricky
 *
 * Created on 2 août 2021, 18:01
 */

#ifndef LINE_H
#define LINE_H

#include <cassert>
#include <iosfwd>


namespace ngn {
    
    class Line {
    public:
        Line();
        Line(int unsigned index1, int unsigned index2);
        
        int unsigned const & getVertexIndex(int i) const;
        int unsigned const * pointerToIndices()const;
        int unsigned getNumberOfVertexIndices()const;

    private:
        int unsigned indices_[2];

        bool valid(int unsigned index1, int unsigned index2)const;
    };
    
    std::ostream & operator<<(std::ostream & out, Line const & line);
}


#endif /* LINE_H */
