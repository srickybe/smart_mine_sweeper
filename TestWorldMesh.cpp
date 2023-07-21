#include <GL/glu.h>
#include <iostream>
#include "TestWorldMesh.h"
#include "Math.h"
#include "MeshBuilder.h"
#include "Partitions.h"
#include "Renderer.h"


namespace ngn {
	
	TestWorldMesh::TestWorldMesh() :
		height(1280),
		width(960),
        ambient_light(new GLfloat[4]{0.9f, 0.9f, 0.9f, 1.0f}),
        diffuse_light(new GLfloat[4]{0.9f, 0.9f, 0.9f, 1.0f}),
        specular_light(new GLfloat[4]{0.8f, 0.2f, 0.3f, 1.0f}),
        light_position(new GLfloat[4]{200.0f, 200.0f, 200.0f, 0.0f}),
		color_blue(new float[4]{.5f, .5f, .5f, 0.5f}),
		specular_reflection(new float[4]{0.8f, 0.3f, 0.3f, 1.0f}),
		axisAngle(ngn::Vector3D::y_axis(), -ngn::Math<Real>::PI / 180.0),
		rotation(ngn::Matrix3D::fromAxisAngle(axisAngle)),
		z_rotation(),
		y_rotation(),
		alpha(0),
		beta(0),
		position(150, 150, 150),
		target(),
		up(),
		basis(	
			1000, 0, 0,
			0, 1000, 0,
			0, 0, 1000
		),
		event(),
		last_time(SDL_GetTicks()),
		current_time(SDL_GetTicks()),
		elapsed_time(0),
		mode(GL_FILL),
		on(true),
		warp_mouse(false),
		increment(10),
		meshColor(1.0f, 1.0f, 1.0f)
	{
		Partitions partitions(25, 25, 1);
		std::shared_ptr<std::vector<ngn::Vector3D>> vertices(new std::vector<ngn::Vector3D>());
		std::shared_ptr<std::vector<ngn::Line>> lines(new std::vector<ngn::Line>());
		ngn::Real minX = 0;
		ngn::Real maxX = 1000;
		ngn::Real minY = 0;
		ngn::Real maxY = 1000;
		ngn::Real minZ = 0;
		//ngn::Real maxZ = 100;
		ngn::Real xCoord = minX;
		
		for (int i = 0; i <= partitions.getXAxisPartitions(); ++i) {
			vertices->push_back(ngn::Vector3D(xCoord, minY, minZ));
			vertices->push_back(ngn::Vector3D(xCoord, maxY, minZ));
			lines->push_back(ngn::Line(vertices->size() - 2, vertices->size() - 1));
			xCoord += ((maxX - minX) / partitions.getXAxisPartitions());
		}
		
		ngn::Real yCoord = minY;
		
		for (int i = 0; i <= partitions.getYAxisPartitions(); ++i) {
			vertices->push_back(ngn::Vector3D(minX, yCoord, minZ));
			vertices->push_back(ngn::Vector3D(maxX, yCoord, minZ));
			lines->push_back(ngn::Line(vertices->size() - 2, vertices->size() - 1));
			yCoord += ((maxY - minY) / partitions.getYAxisPartitions());
		}
		
		mesh.setPoints(vertices);
		mesh.setLines(lines);
	}
	
	TestWorldMesh::~TestWorldMesh() {
	}
	
	void TestWorldMesh::start() {
        SDL_Init(SDL_INIT_VIDEO);
        atexit(SDL_Quit);
        SDL_WM_SetCaption("SDL GL Application", NULL);
        SDL_SetVideoMode(height, width, 32, SDL_OPENGL);
        SDL_WarpMouse(height / 2, width / 2);

        // Set color and depth clear value
        glClearDepth(1.f);
        glClearColor(0.75f, 0.75f, 0.75f, 1.f);

        // Enable Z-buffer read and write
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);

        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90.f, (float) height / (float) width, 1.f, 1000000.f);

        // Enable lighting
        // Somewhere in the initialization part of your program
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);				
        glEnable(GL_COLOR_MATERIAL);

        // Assign created components to GL_LIGHT0
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light.get());
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light.get());
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light.get());
        glLightfv(GL_LIGHT0, GL_POSITION, light_position.get());
		
        //SDL_EnableKeyRepeat(20, 20);
		SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
        glPolygonMode(GL_FRONT_AND_BACK, mode);
		
		loop();
		SDL_Quit();
	}
	
	void TestWorldMesh::draw() {
		glPolygonMode(GL_FRONT_AND_BACK, mode);

		current_time = SDL_GetTicks();
		elapsed_time = current_time - last_time;
		last_time = current_time;

		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Apply some transformations
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//define view
		target = ngn::Vector3D::add(position, rotation.getCol(0));
		up = rotation.getCol(2);

		gluLookAt(
			position.getX(),
			position.getY(),
			position.getZ(),
			target.getX(),
			target.getY(),
			target.getZ(),
			up.getX(),
			up.getY(),
			up.getZ()
		);

		//position = ngn::Matrix3D::mult( rotation, position );

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_blue.get());
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_reflection.get());
		glMateriali(GL_FRONT, GL_SHININESS, 192);

		Renderer render;
		render.render(ngn::Vector3D::zero(), basis);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(meshColor.getR(), meshColor.getG(), meshColor.getB());
		
		render.render(mesh);


		SDL_GL_SwapBuffers();

		if (elapsed_time < 40) {
			SDL_Delay(40 - elapsed_time);
		}

		if (warp_mouse) {
			SDL_WarpMouse(640, 480);
			warp_mouse = false;
		}
	}
	
	void TestWorldMesh::loop() {
		while (on) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_MOUSEMOTION:
						onSDLMouseMotion(event);
						break;

					case SDL_QUIT:
						onSDLQuit(event);
						break;

					case SDL_KEYDOWN:
						onSDLKeyDown(event);
						break;
					
                    default:
                        break;
				}
			}
			
			draw();
		}
	}
	
	void TestWorldMesh::onSDLMouseMotion(SDL_Event & event) {
		alpha -= event.motion.xrel * ngn::Math<Real>::PI / width;
		beta += event.motion.yrel * ngn::Math<Real>::PI / height;

		if (beta > ngn::Math<Real>::PI / 2 - ngn::Math<Real>::PI / 36) {
			beta = ngn::Math<Real>::PI / 2 - ngn::Math<Real>::PI / 36;
		} else {
			if (beta < -ngn::Math<Real>::PI / 2 + ngn::Math<Real>::PI / 36) {
				beta = -ngn::Math<Real>::PI / 2 + ngn::Math<Real>::PI / 36;
			}
		}

		z_rotation = ngn::Matrix3D::fromAxisAngle(ngn::AxisAngle(ngn::Vector3D::y_axis(), alpha));
		y_rotation = ngn::Matrix3D::fromAxisAngle(ngn::AxisAngle(ngn::Vector3D::x_axis(), beta));
		rotation = z_rotation.mult(y_rotation).mult(ngn::Matrix3D(0, 1, 0, 0, 0, 1, 1, 0, 0));
	}
	
	void TestWorldMesh::onSDLQuit(SDL_Event & event) {
		on = false;
	}
	
	void TestWorldMesh::onSDLKeyDown(SDL_Event & event) {
		switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				onSpaceKey(event);
				break;

			case SDLK_ESCAPE:
				onEscapeKey(event);
				break;

			case SDLK_w:
				onWKey(event);
				break;

			case SDLK_LEFT:
				onLeftKey(event);
				break;

			case SDLK_RIGHT:
				onRightKey(event);
				break;

			case SDLK_UP:
				onUPKey(event);
				break;

			case SDLK_DOWN:
				onDownKey(event);
				break;

			case SDLK_a:
				onAKey(event);
				break;

			case SDLK_c:
				onCKey(event);
				break;
				
			case SDLK_q:
				onQKey(event);
				break;

			case SDLK_KP_PLUS:
				onPlusKey(event);
				break;

			case SDLK_KP_MINUS:
				onMinusKey(event);
				break;

			case SDLK_r:
				onRKey(event);
				break;

			case SDLK_g:
				onGKey(event);
				break;

			case SDLK_b:
				onBKey(event);
				break;

			case SDLK_n:
				onNKey(event);
				break;

			case SDLK_h:
				onHKey(event);
				break;

			case SDLK_t:
				onTKey(event);
				break;

			default:
				break;
		}
	}
		
	void TestWorldMesh::onSpaceKey(SDL_Event & event) { 
		if (mode == GL_FILL) {
			mode = GL_LINE;
		} else {
			if (mode == GL_LINE) {
				mode = GL_FILL;
			}
		}		
	}
	
	void TestWorldMesh::onEscapeKey(SDL_Event & event) { 
		on = false;
	}
	
	void TestWorldMesh::onWKey(SDL_Event & event) { 
		warp_mouse = true;
	}
	
	void TestWorldMesh::onLeftKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(-increment, 0, 0));
	}
	
	void TestWorldMesh::onRightKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(increment, 0, 0));
	}
	
	void TestWorldMesh::onUPKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(0, increment, 0));
	}
	
	void TestWorldMesh::onDownKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(0, -increment, 0));
	}
	
	void TestWorldMesh::onAKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(0, 0, increment));
	}
	
	void TestWorldMesh::onCKey(SDL_Event & event) { }
	
	void TestWorldMesh::onQKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(0, 0, -increment));
	}
	
	void TestWorldMesh::onPlusKey(SDL_Event & event) { 
	}
	
	void TestWorldMesh::onMinusKey(SDL_Event & event) { 
	}
	
	void TestWorldMesh::onRKey(SDL_Event & event) { 
		meshColor.incrementR(0.01f);	
	}
	
	void TestWorldMesh::onGKey(SDL_Event & event) { 
		meshColor.incrementG(0.01f);
	}
	
	void TestWorldMesh::onBKey(SDL_Event & event) { 
		meshColor.incrementB(0.01f);
	}
	
	void TestWorldMesh::onNKey(SDL_Event & event) { 
		meshColor.incrementR(-0.01f);
	}
	
	void TestWorldMesh::onHKey(SDL_Event & event) { 
		meshColor.incrementG(-0.01f);
	}
	
	void TestWorldMesh::onTKey(SDL_Event & event) { 
		meshColor.incrementB(-0.01f);
	}
		
	void testWorldMesh() {
    }
}
