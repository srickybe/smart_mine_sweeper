#ifndef TEST_ICOSAHEDRON_H
#define TEST_ICOSAHEDRON_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <memory>
#include <SDL/SDL.h>
#include <vector>
#include "AxisAngle.h"
#include "Matrix3D.h"
#include "Mesh.h"
#include "Real.h"
#include "RGBColor.h"
#include "Vector3D.h"

namespace ngn {
	
	class TestIcosahedron {
	public:
		TestIcosahedron(int argc, char ** argv);
		~TestIcosahedron();
		void start();
		
	private:
		std::vector<std::shared_ptr<Mesh>> icosahedrons;
		Real radius;
		int levelOfDetail;
		int height;
		int width;
		
		/*light components*/
        std::shared_ptr<GLfloat> ambient_light;
        std::shared_ptr<GLfloat> diffuse_light;
        std::shared_ptr<GLfloat> specular_light;
        std::shared_ptr<GLfloat> light_position;
		
		/*mini_obj material properties*/
        std::shared_ptr<float> color_blue;
        std::shared_ptr<float> specular_reflection;

		/*camera properties*/
		ngn::AxisAngle axisAngle;
        ngn::Matrix3D rotation;
        ngn::Matrix3D z_rotation;
        ngn::Matrix3D y_rotation;
        Real alpha;
        Real beta;
        ngn::Vector3D position;
        ngn::Vector3D target;
        ngn::Vector3D up;
        ngn::Matrix3D basis;
		
		/*SDL properties*/
		SDL_Event event;
        Uint32 last_time;
        Uint32 current_time;
        Uint32 elapsed_time;
        GLenum mode;
        bool on;
        bool warp_mouse;
        float increment;
        RGBColor meshColor;
		
		void draw();
		void loop();
		void onSDLMouseMotion(SDL_Event & event);
		void onSDLQuit(SDL_Event & event);
		void onSDLKeyDown(SDL_Event & event);
		
		void onSpaceKey(SDL_Event & event);
		void onEscapeKey(SDL_Event & event);
		void onWKey(SDL_Event & event);
		void onLeftKey(SDL_Event & event);
		void onRightKey(SDL_Event & event);
		void onUPKey(SDL_Event & event);
		void onDownKey(SDL_Event & event);
		void onAKey(SDL_Event & event);
		void onCKey(SDL_Event & event);
		void onQKey(SDL_Event & event);
		void onPlusKey(SDL_Event & event);
		void onMinusKey(SDL_Event & event);
		void onRKey(SDL_Event & event);
		void onGKey(SDL_Event & event);
		void onBKey(SDL_Event & event);
		void onNKey(SDL_Event & event);
		void onHKey(SDL_Event & event);
		void onTKey(SDL_Event & event);
	};
	
    void testIcosahedron(int argc, char ** argv);
}

#endif /* TEST_ICOSAHEDRON_H */
