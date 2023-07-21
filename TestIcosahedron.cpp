#include "TestIcosahedron.h"
#include <cassert>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <SDL/SDL.h>
#include <vector>

#include "AxisAngle.h"
#include "BoundingVolumeBuilder3D.h"
#include "ComputeTrianglesAreas.h"
#include "ComputeTrianglesCenters.h"
#include "Renderer.h"
#include "GaussPointsFit.h"
#include "GaussTrianglesFit.h"
#include "OBJLoader.h"
#include "ModelLoader.h"
#include "MaterialManager.h"
#include "Math.h"
#include "Matrix3D.h"
#include "MeshBuilder.h"
#include "Model.h"
#include "Octree.h"
#include "OrientedBox3D.h"
#include "OrientedBox3DTree.h"
#include "Real.h"
#include "Sphere.h"
#include "SphereTree.h"
#include "Triangle.h"
#include "Utility.h"
#include "Vector3D.h"

namespace ngn {
	
	TestIcosahedron::TestIcosahedron(int argc, char ** argv) :
		icosahedrons(),
		radius(125.0),
		levelOfDetail(0),
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
		MeshBuilder meshBuilder;
        icosahedrons.push_back(meshBuilder.icosahedron(radius));
	}
	
	TestIcosahedron::~TestIcosahedron() {
	}
	
	void TestIcosahedron::start() {
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
	
	void TestIcosahedron::draw() {
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
		
		render.render(*icosahedrons.operator [](levelOfDetail));


		SDL_GL_SwapBuffers();

		if (elapsed_time < 40) {
			SDL_Delay(40 - elapsed_time);
		}

		if (warp_mouse) {
			SDL_WarpMouse(640, 480);
			warp_mouse = false;
		}
	}
	
	void TestIcosahedron::loop() {
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
	
	void TestIcosahedron::onSDLMouseMotion(SDL_Event & event) {
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
	
	void TestIcosahedron::onSDLQuit(SDL_Event & event) {
		on = false;
	}
	
	void TestIcosahedron::onSDLKeyDown(SDL_Event & event) {
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
		
	void TestIcosahedron::onSpaceKey(SDL_Event & event) { 
		if (mode == GL_FILL) {
			mode = GL_LINE;
		} else {
			if (mode == GL_LINE) {
				mode = GL_FILL;
			}
		}		
	}
	
	void TestIcosahedron::onEscapeKey(SDL_Event & event) { 
		on = false;
	}
	
	void TestIcosahedron::onWKey(SDL_Event & event) { 
		warp_mouse = true;
	}
	
	void TestIcosahedron::onLeftKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(-increment, 0, 0));
	}
	
	void TestIcosahedron::onRightKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(increment, 0, 0));
	}
	
	void TestIcosahedron::onUPKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(0, increment, 0));
	}
	
	void TestIcosahedron::onDownKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(0, -increment, 0));
	}
	
	void TestIcosahedron::onAKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(0, 0, increment));
	}
	
	void TestIcosahedron::onCKey(SDL_Event & event) { }
	
	void TestIcosahedron::onQKey(SDL_Event & event) { 
		position.add(ngn::Vector3D(0, 0, -increment));
	}
	
	void TestIcosahedron::onPlusKey(SDL_Event & event) { 
		++levelOfDetail;
		std::cout << "levelOfDetail = " << levelOfDetail << "\n";
		//std::cout << "icosahedrons.size() = " << icosahedrons.size() << "\n";

		if ((int)icosahedrons.size() <= levelOfDetail) {
			MeshBuilder meshBuilder;
			std::shared_ptr<Mesh> mostDetailedIcosahedron = icosahedrons.operator [](icosahedrons.size() - 1);
			std::shared_ptr<Mesh> icosahedron = meshBuilder.refineIcosahedron(*mostDetailedIcosahedron, radius);
			icosahedrons.push_back(icosahedron);
			std::cout << "number of vertices = " << icosahedron->getPoints()->size() << "\n";
			std::cout << "number of triangles = " << icosahedron->getTriangles()->size() << "\n";
		}
	}
	
	void TestIcosahedron::onMinusKey(SDL_Event & event) { 
		if (levelOfDetail > 0) {
			--levelOfDetail;
		}
		
		std::cout << "levelOfDetail = " << levelOfDetail << "\n";
		std::cout << "number of vertices = " << icosahedrons[levelOfDetail]->getPoints()->size() << "\n";
		std::cout << "number of triangles = " << icosahedrons[levelOfDetail]->getTriangles()->size() << "\n";
	}
	
	void TestIcosahedron::onRKey(SDL_Event & event) { 
		meshColor.incrementR(0.01f);	
	}
	
	void TestIcosahedron::onGKey(SDL_Event & event) { 
		meshColor.incrementG(0.01f);
	}
	
	void TestIcosahedron::onBKey(SDL_Event & event) { 
		meshColor.incrementB(0.01f);
	}
	
	void TestIcosahedron::onNKey(SDL_Event & event) { 
		meshColor.incrementR(-0.01f);
	}
	
	void TestIcosahedron::onHKey(SDL_Event & event) { 
		meshColor.incrementG(-0.01f);
	}
	
	void TestIcosahedron::onTKey(SDL_Event & event) { 
		meshColor.incrementB(-0.01f);
	}
		
	void testIcosahedron(int argc, char ** argv) {
		/*std::cout << "void testIcosahedron(int argc, char ** argv)\n";
        MeshBuilder mb;
        std::vector<std::shared_ptr<Mesh>> icosahedrons;
		std::vector<std::shared_ptr<Mesh>> icos;
		Real radius = 125.0;
        icosahedrons.push_back(mb.icosahedron(radius));
        icosahedrons.operator[](0) = mb.simplifyIcosahedron(*icosahedrons.operator[](0));
		icos.push_back(mb.icosahedron(radius));
		int levelOfDetail = 0;
		icos.operator [](0) = mb.icosahedron(radius, levelOfDetail);
        ngn::Renderer draw;

        SDL_Init(SDL_INIT_VIDEO);
        atexit(SDL_Quit);
        SDL_WM_SetCaption("SDL GL Application", NULL);
        int width = 960;
        int height = 1280;
        SDL_SetVideoMode(height, width, 32, SDL_OPENGL);
        SDL_WarpMouse(height / 2, width / 2);

        // Set color and depth clear value
        glClearDepth(1.f);
        glClearColor(0.f, 0.f, 0.f, 0.f);

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

        // Create light components
        GLfloat ambient_light[] = {0.9f, 0.9f, 0.9f, 1.0f};
        GLfloat diffuse_light[] = {0.9f, 0.9f, 0.9f, 1.0f};
        GLfloat specular_light[] = {0.8f, 0.2f, 0.3f, 1.0f};
        GLfloat light_position[] = {1000.0f, 1000.0f, 1000.0f, 0.0f};

        // Assign created components to GL_LIGHT0
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        //mini_obj material properties
        float color_blue[] = {.5f, .5f, .5f, 0.5f};
        float specular_reflection[] = {0.4f, 0.3f, 0.3f, 1.0f};

        ngn::AxisAngle axisAngle(ngn::Vector3D::y_axis(), -ngn::Math<Real>::PI / 180.0);
        ngn::Matrix3D rotation = ngn::Matrix3D::fromAxisAngle(axisAngle);
        ngn::Matrix3D z_rotation;
        ngn::Matrix3D y_rotation;
        Real alpha = 0;
        Real beta = 0;
        ngn::Vector3D position(150, 150, 150);//atof(argv[2]), atof(argv[3]), atof(argv[4]));
		cout << "position = " << position << "\n";
        ngn::Vector3D target;
        ngn::Vector3D up;

        ngn::Matrix3D basis(
                1000, 0, 0,
                0, 1000, 0,
                0, 0, 1000
                );

        Uint32 last_time = SDL_GetTicks();
        Uint32 current_time;
        Uint32 elapsed_time;
        SDL_Event event;
        SDL_EnableKeyRepeat(20, 20);
        GLenum mode = GL_FILL;
        glPolygonMode(GL_FRONT_AND_BACK, mode);
        bool on = true;
        bool warp_mouse = false;
        //int depth = atoi(argv[6]);
        float increment = 10.0; //atof(argv[5]);
        RGBColor meshColor(1.0f, 1.0f, 1.0f);
		bool drawFlag = true;

        // Start game loop
        while (on) {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_MOUSEMOTION:
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

                        break;

                    case SDL_QUIT:
                        on = false;
                        break;

                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym) {
                            case SDLK_SPACE:
                                if (mode == GL_FILL) {
                                    mode = GL_LINE;
                                } else {
                                    if (mode == GL_LINE) {
                                        mode = GL_FILL;
                                    }
                                }

                                break;

                            case SDLK_ESCAPE:
                                on = false;
                                break;

                            case SDLK_w:
                                warp_mouse = true;
                                break;

                            case SDLK_LEFT:
                                position.add(ngn::Vector3D(-increment, 0, 0));
                                break;

                            case SDLK_RIGHT:
                                position.add(ngn::Vector3D(increment, 0, 0));
                                break;

                            case SDLK_UP:
                                position.add(ngn::Vector3D(0, increment, 0));
                                break;

                            case SDLK_DOWN:
                                position.add(ngn::Vector3D(0, -increment, 0));
                                break;

                            case SDLK_a:
                                position.add(ngn::Vector3D(0, 0, increment));
                                break;

							case SDLK_c:
								drawFlag = !drawFlag;
								break;
								
                            case SDLK_q:
                                position.add(ngn::Vector3D(0, 0, -increment));
                                break;

                            case SDLK_KP_PLUS:
                                ++levelOfDetail;
                                std::cout << "levelOfDetail = " << levelOfDetail << "\n";
								std::cout << "icosahedrons.size() = " << icosahedrons.size() << "\n";

                                if ((int)icosahedrons.size() <= levelOfDetail) {
                                    icosahedrons.push_back(mb.refineIcosahedron(*icosahedrons.operator [](icosahedrons.size() - 1)));
                                    icosahedrons.operator[](icosahedrons.size() - 1) 
										= mb.simplifyIcosahedron(*icosahedrons.operator[](icosahedrons.size() - 1));
                                    std::cout << "###number of vertices = ";
									std::cout << icosahedrons.operator[](icosahedrons.size() - 1)->getPoints()->size() << "\n";
                                    std::cout << "###number of triangles = "; 
									std::cout << icosahedrons.operator[](icosahedrons.size() - 1)->getTriangles()->size() << "\n";

                                    icos.push_back(mb.icosahedron(radius, levelOfDetail));
                                    std::cout << "number of vertices = " << icos[icos.size()-1]->getPoints()->size() << "\n";
                                    std::cout << "number of triangles = " << icos[icos.size()-1]->getTriangles()->size() << "\n";
                                    //icosahedrons.push_back(mb.refineIcosahedron(icosahedrons.operator [](icosahedrons.size() - 1)));
                                    //icosahedrons.operator[](icosahedrons.size() - 1) = mb.simplifyIcosahedron(icosahedrons.operator[](icosahedrons.size() - 1));
                                }
								
                                break;

                            case SDLK_KP_MINUS:
                                if (levelOfDetail == 0) {
                                    levelOfDetail = 0;
                                } else if (levelOfDetail > 0) {
									--levelOfDetail;
								}
								
								std::cout << "levelOfDetail = " << levelOfDetail << "\n";

                                break;

                            case SDLK_r:
                                if (meshColor.getR() + 0.01f < 1.0f) {
                                    meshColor = RGBColor(meshColor.getR() + 0.01f, meshColor.getG(), meshColor.getB());
                                } else {
                                    meshColor = RGBColor(1.0f, meshColor.getG(), meshColor.getB());
                                }
                                break;

                            case SDLK_g:
                                if (meshColor.getG() + 0.01f < 1.0f) {
                                    meshColor = RGBColor(meshColor.getR(), meshColor.getG() + 0.01f, meshColor.getB());
                                } else {
                                    meshColor = RGBColor(meshColor.getR(), 1.0f, meshColor.getB());
                                }
                                break;

                            case SDLK_b:
                                if (meshColor.getB() + 0.01f) {
                                    meshColor = RGBColor(meshColor.getR(), meshColor.getG(), meshColor.getB() + 0.01f);
                                } else {
                                    meshColor = RGBColor(meshColor.getR(), meshColor.getG(), 1.0f);
                                }
                                break;

                            case SDLK_n:
                                if (meshColor.getB() - 0.01f > 0.0f) {
                                    meshColor = RGBColor(meshColor.getR(), meshColor.getG(), meshColor.getB() - 0.01f);
                                } else {
                                    meshColor = RGBColor(meshColor.getR(), meshColor.getG(), 0.0f);
                                }
                                break;

                            case SDLK_h:
                                if (meshColor.getG() - 0.01f > 0.0f) {
                                    meshColor = RGBColor(meshColor.getR(), meshColor.getG() - 0.01f, meshColor.getB());
                                } else {
                                    meshColor = RGBColor(meshColor.getR(), 0.0f, meshColor.getB());
                                }
                                break;

                            case SDLK_t:
                                if (meshColor.getR() - 0.01f > 0.0f) {
                                    meshColor = RGBColor(meshColor.getR() - 0.01f, meshColor.getG(), meshColor.getB());
                                } else {
                                    meshColor = RGBColor(0.0f, meshColor.getG(), meshColor.getB());
                                }
                                break;

                            default:
                                break;
                        }

                        break;

                    default:
                        break;
                }
            }

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

            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_blue);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular_reflection);
            glMateriali(GL_FRONT, GL_SHININESS, 192);


            draw.render(ngn::Vector3D::zero(), basis);


            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glColor3f(meshColor.getR(), meshColor.getG(), meshColor.getB());
            
			if (drawFlag) {
				draw.render(*icos.operator [](levelOfDetail));
			} else {
				draw.render(*icosahedrons.operator [](levelOfDetail));
			}
			//draw.render(Sphere(Vector3D::zero(), radius));


            SDL_GL_SwapBuffers();

            if (elapsed_time < 40) {
                SDL_Delay(40 - elapsed_time);
            }

            if (warp_mouse) {
                SDL_WarpMouse(640, 480);
                warp_mouse = false;
            }
        }

        SDL_Quit();*/
    }
}