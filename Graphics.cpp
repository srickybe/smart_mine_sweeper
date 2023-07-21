#include "Graphics.h"
#include "Math.h"
#include "MeshBuilder.h"
#include "PhysicObject3D.h"
#include "Renderer.h"

namespace ngn {
	
	Graphics::Graphics() :
		objects(),
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
	}
	
	void Graphics::setGraphicObjects(std::shared_ptr<std::vector<SharedPtrGraphicObject>> const & objs) {
		objects = objs;
	}
	
	void Graphics::start() {
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
		
		//loop();
	}
	
	void Graphics::draw() {
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

		Renderer renderer;
		renderer.render(ngn::Vector3D::zero(), basis);

		for (int unsigned i = 0; i < 0/*objects->size()*/; ++i) {
			SharedPtrGraphicObject object = objects->operator [](i);
			
			renderer.render(
				object->getPosition(), 
				object->getOrientation(), 
				*object->getMesh()
			);
		}

		SDL_GL_SwapBuffers();

		if (elapsed_time < 40) {
			SDL_Delay(40 - elapsed_time);
		}

		if (warp_mouse) {
			SDL_WarpMouse(640, 480);
			warp_mouse = false;
		}
	}
	
	void Graphics::loop() {
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
		
		SDL_Quit();
	}
	
	void Graphics::onSDLMouseMotion(SDL_Event & event) {
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
	
	void Graphics::onSDLQuit(SDL_Event & event) {
		on = false;
	}
	
	void Graphics::onSDLKeyDown(SDL_Event & event) {
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
		
	void Graphics::onSpaceKey(SDL_Event & event) { 
		if (mode == GL_FILL) {
			mode = GL_LINE;
		} else {
			if (mode == GL_LINE) {
				mode = GL_FILL;
			}
		}		
	}
	
	void Graphics::onEscapeKey(SDL_Event & event) { 
		on = false;
	}
	
	void Graphics::onWKey(SDL_Event & event) { 
		warp_mouse = true;
	}
	
	void Graphics::onLeftKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(-increment, 0, 0));
	}
	
	void Graphics::onRightKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(increment, 0, 0));
	}
	
	void Graphics::onUPKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(0, increment, 0));
	}
	
	void Graphics::onDownKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(0, -increment, 0));
	}
	
	void Graphics::onAKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(0, 0, increment));
	}
	
	void Graphics::onCKey(SDL_Event & event) { }
	
	void Graphics::onQKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(0, 0, -increment));
	}
	
	void Graphics::onPlusKey(SDL_Event & event) { 
	}
	
	void Graphics::onMinusKey(SDL_Event & event) { 
	}
	
	void Graphics::onRKey(SDL_Event & event) { 
		meshColor.incrementR(0.01f);	
	}
	
	void Graphics::onGKey(SDL_Event & event) { 
		meshColor.incrementG(0.01f);
	}
	
	void Graphics::onBKey(SDL_Event & event) { 
		meshColor.incrementB(0.01f);
	}
	
	void Graphics::onNKey(SDL_Event & event) { 
		meshColor.incrementR(-0.01f);
	}
	
	void Graphics::onHKey(SDL_Event & event) { 
		meshColor.incrementG(-0.01f);
	}
	
	void Graphics::onTKey(SDL_Event & event) { 
		meshColor.incrementB(-0.01f);
	}
}