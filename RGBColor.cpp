#include "RGBColor.h"
#include <iostream>
#include "Math.h"

namespace ngn {
	
	RGBColor RGBColor::BLACK = RGBColor(0.0f, 0.0f, 0.0f);
	RGBColor RGBColor::BLUE = RGBColor(0.0f, 0.0f, 1.0f);
	RGBColor RGBColor::GREEN = RGBColor(0.0f, 1.0f, 0.0f);
	RGBColor RGBColor::RED = RGBColor(1.0f, 0.0f, 0.0f);
	
	GLint RGBColor::numberOfComponents = 3;
	GLenum const RGBColor::componentsType = GL_FLOAT;
	
    RGBColor::RGBColor()
    : r(1.0f), g(1.0f), b(1.0f) {
    }

    RGBColor::RGBColor(GLfloat r, GLfloat g, GLfloat b)
    : r(r), g(g), b(b) {
    }

    bool RGBColor::equals(RGBColor const & rhs, float tol) const {
        return Math<float>::areEqualWithTol(r, rhs.r, tol) 
				&& Math<float>::areEqualWithTol(g, rhs.g, tol) 
				&& Math<float>::areEqualWithTol(b, rhs.b, tol);
    }
    
	GLfloat RGBColor::getR() const {
		return r;
	}
	
	GLfloat RGBColor::getG() const {
		return g;
	}
	
	GLfloat RGBColor::getB() const {
		return b;
	}

	void RGBColor::incrementR(GLfloat val) {
		r += val;
		
		if (r > 1.0f) {
			r = 1.0f;
		} else if (r < 0.0f) {
			r = 0.0f;
		}
	}
	
	void RGBColor::incrementG(GLfloat val) {
		g += val;
		
		if (g > 1.0f) {
			g = 1.0f;
		} else if (g < 0.0f) {
			g = 0.0f;
		}	
	}
	
	void RGBColor::incrementB(GLfloat val) {
		b += val;
		
		if (b > 1.0f) {
			b = 1.0f;
		} else if (b < 0.0f) {
			b = 0.0f;
		}	
	}
	
	GLfloat const * RGBColor::pointerToComponents() const {
		return &r;
	}
	
    std::ostream & operator<<(std::ostream & out, RGBColor const & color) {
        out << "( " << color.getR() << ", " << color.getG() << ", " << color.getB() << " )";
        
        return out;
    }
}