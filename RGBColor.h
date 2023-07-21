#ifndef RGB_COLOR_H
#define RGB_COLOR_H

#include <iosfwd>
#include <GL/gl.h>

namespace ngn {
	
	class RGBColor {
	public:
		static RGBColor BLACK;
		static RGBColor BLUE;
		static RGBColor GREEN;
		static RGBColor RED;
		static GLint numberOfComponents;
		static const GLenum componentsType;
		
		RGBColor();
		RGBColor(GLfloat, GLfloat, GLfloat);

		bool equals(RGBColor const & rhs, float tol) const;
		GLfloat getR() const;
		GLfloat getG() const;
		GLfloat getB() const;
		
		void incrementR(GLfloat val);
		void incrementG(GLfloat val);
		void incrementB(GLfloat val);
		
		GLfloat const * pointerToComponents() const;

	private:
		GLfloat r;
		GLfloat g;
		GLfloat b;
    };

    std::ostream & operator<<(std::ostream &, RGBColor const &);
}

#endif // RGB_COLOR_H