#ifndef TRAITS_H
#define TRAITS_H

#include <GL/gl.h>
#include <GL/glu.h>

namespace ngn {
	
    template< typename Real >
    struct Traits {
    };

    template<>
    struct Traits< double > {
        static const GLenum real_t = GL_DOUBLE;
		
		static void glRotate(double a, double x, double y, double z) {
			glRotated(a, x, y, z);
		}
		
		static void glScale(double x, double y, double z) {
			glScaled(x, y, z);
		}
		
		static void glTranslate(double x, double y, double z) {
			glTranslated(x, y, z);
		}
		
		static void glVertex3(double x, double y, double z) {
			glVertex3d(x, y, z);
		}
    };

    template<>
    struct Traits< float > {
        static const GLenum real_t = GL_FLOAT;
		
		static void glRotate(float a, float x, float y, float z) {
			glRotatef(a, x, y, z);
		}
		
		static void glScale(float x, float y, float z) {
			glScaled(x, y, z);
		}
		
		static 	void glTranslate(float x, float y, float z) {
			glTranslatef(x, y, z);
		}
		
		static void glVertex3(float x, float y, float z) {
			glVertex3f(x, y, z);
		}
    };

    template<>
    struct Traits< int > {
        static const GLenum real_t = GL_INT;
    };
}

#endif // TRAITS_H