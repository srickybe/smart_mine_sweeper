#ifndef TEST_SIMULATION_H
#define TEST_SIMULATION_H

#include <GL/gl.h>
#include <memory>
#include <SDL/SDL.h>
#include <vector>
#include "AxisAngle.h"
#include "Camera.h"
#include "Matrix3D.h"
#include "Mesh.h"
#include "Real.h"
#include "Parameters.h"
#include "RGBColor.h"
#include "Simulation.h"
#include "SteeringFunction.h"

/*
CAMERA movement:
w : forwards
s : backwards
a : turn left
d : turn right
x : turn up
y : turn down
v : strafe right
c : strafe left
r : move up
f : move down
m/n : roll*/

namespace smrtsw {
	
	class Application {
	public:
		Application(
			ai::Parameters const & params, 
			SharedPtrSteeringFunction const & steeringFunc
		);
		
		void start();
		void sleep();
		Real elapsedTime();
		
	private:
		int height;
		int width;
		
		/**/
		std::shared_ptr<std::vector<smrtsw::SharedPtrSmartMineSweeper>> sweepers;
		std::shared_ptr<std::vector<smrtsw::SharedPtrMine>> mines;
		
		/*light components*/
        std::shared_ptr<GLfloat> ambient_light;
        std::shared_ptr<GLfloat> diffuse_light;
        std::shared_ptr<GLfloat> specular_light;
        std::shared_ptr<GLfloat> light_position;
		
		/*mini_obj material properties*/
        std::shared_ptr<float> color_blue;
        std::shared_ptr<float> specular_reflection;

		/*camera properties*/
		Camera camera;
		Real dx;
		Real dy;
        ngn::Matrix3D basis;
		
		/*SDL properties*/
		SDL_Event event;
        //Uint32 last_time;
        //Uint32 current_time;
        //Uint32 elapsed_time;
        GLenum mode;
        bool on;
        bool warp_mouse;
        float increment;
        ngn::RGBColor xyPlaneMeshColor;
		
		/**/
		ai::Parameters parameters;
		SharedPtrSteeringFunction steeringFunction;
		Simulation simulation;
		Renderer renderer;
		ngn::Mesh xyPlaneMesh;
		OrientedBox3D floor;
		std::vector<OrientedBox3D> sweeperGeometries;
		SharedPtrMesh sweeperBoundingSphereMesh;
		SharedPtrMesh mineMesh;
		bool shouldDraw;
		bool shouldRunOnline;
		bool shouldDrawBoundingSpheres;
		int sleepTimeMillis;
		Real frameTime;
		
		void initializeFloor();
		void initializeSweeperGeometries();
		void initializeSweepersAndMines();
		void initializeXYPlaneMesh();
		void draw();
		void drawBoundingSphereOfSweeper(SharedPtrSmartMineSweeper const & sweeper) const;
		void drawDirectionToClosestMineFromSweeper(SharedPtrSmartMineSweeper const & sweeper) const;
		void drawSweeper(SharedPtrSmartMineSweeper const & sweeper) const; 
		void loop();
		void onSDLMouseMotion(SDL_Event & event);
		void onSDLQuit(SDL_Event & event);
		void onSDLKeyDown(SDL_Event & event);
		
		void onSpaceKey(SDL_Event & event);
		void onEscapeKey(SDL_Event & event);
		void onAKey(SDL_Event & event);
		void onBKey(SDL_Event & event);
		void onCKey(SDL_Event & event);
		void onDKey(SDL_Event & event);
		void onFKey(SDL_Event & event);
		void onHKey(SDL_Event & event);
		void onMKey(SDL_Event & event);
		void onNKey(SDL_Event & event);
		void onPKey(SDL_Event & event);
		void onRKey(SDL_Event & event);
		void onSKey(SDL_Event & event);
		void onVKey(SDL_Event & event);
		void onXKey(SDL_Event & event);
		void onYKey(SDL_Event & event);
		void onWKey(SDL_Event & event);
		
		void renderMine(SharedPtrMine const & mine) const;
		void renderSweeper(SharedPtrSmartMineSweeper const & sweeper) const;
		void startSimulation();
	};
	
    void testWorldMesh();
}

#endif // TEST_SIMULATION_H