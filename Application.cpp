#include "Application.h"
#include <GL/glu.h>
#include <iostream>
#include "Math.h"
#include "MeshBuilder.h"
#include "OrientedBox3D.h"
#include "Partitions.h"
#include "RandomGeneratorOfSweepersAndMines.h"
#include "Renderer.h"
#include "Sphere.h"
#include "UnsupportedOperationException.h"


namespace smrtsw {
	
	Application::Application(
		ai::Parameters const & params, 
		SharedPtrSteeringFunction const & steeringFunc
	) :
		height(1920),
		width(1080),
		sweepers(),
		mines(),
        ambient_light(new GLfloat[4]{0.9f, 0.9f, 0.9f, 1.0f}),
        diffuse_light(new GLfloat[4]{0.9f, 0.9f, 0.9f, 1.0f}),
        specular_light(new GLfloat[4]{0.8f, 0.2f, 0.3f, 1.0f}),
        light_position(new GLfloat[4]{200.0f, 200.0f, 200.0f, 0.0f}),
		color_blue(new float[4]{.5f, .5f, .5f, 0.5f}),
		specular_reflection(new float[4]{0.8f, 0.3f, 0.3f, 1.0f}),
		camera(
			Camera::fromViewRightUpPositionXYZAngles(
				Vector3D::negate(Vector3D::z_axis()),//Vector3D(height / 2, width / 2, 0),
				/*Vector3D::negate*/(Vector3D::y_axis()),
				Vector3D::negate(Vector3D::x_axis()),
				Vector3D(height / 2, width / 2, (height + width) / 4),
				0, 
				0, 
				0
			)
		),
		basis(	
			1000, 0, 0,
			0, 1000, 0,
			0, 0, 1000
		),
		event(),
		mode(GL_FILL),
		on(true),
		warp_mouse(false),
		increment(10),
		xyPlaneMeshColor(1.0f, 1.0f, 1.0f),
		parameters(params),
		steeringFunction(steeringFunc),
		simulation(),
		renderer(),
		mineMesh(MeshBuilder::icosahedron(params.getMineRadius(), 1)),
		shouldDraw(false),
		shouldRunOnline(false),
		shouldDrawBoundingSpheres(false),
		sleepTimeMillis(1000 / params.getPhysicsUpdateRate()),
		frameTime(1000.0 / params.getPhysicsUpdateRate() / 1000.0)
	{
		std::cout << "Application::Application(...)\n";
		std::cout << "Parameters:\n" << parameters << "\n";
		initializeSweeperGeometries();		
		initializeXYPlaneMesh();
		initializeSweepersAndMines();
		Real radius = sweepers->operator [](0)->getBoundingSphere().getRadius();
		sweeperBoundingSphereMesh = MeshBuilder::icosahedron(radius, 1);
		Settings settings(params.getGASettingsFilePath());
		Vector3D origin = params.getWorldOrigin();
		Vector3D extents = params.getWorldExtents();
		ngn::Partitions partitions(
			parameters.getNumberOfRowsOfSpacePartition(),
			parameters.getNumberOfColumnsOfSpacePartition(),
			1
		);
		Grid3D spacePartition(origin, extents, partitions);
		smrtsw::SharedPtrSteeringFunction steeringFunction;
		
		simulation = Simulation(
			params,
			settings,
			spacePartition,
			sweepers,
			mines,
			steeringFunc
		);
		renderer.setLevelOfDetailOfIcosahedron(1);
		initializeFloor();
	}
	
	void Application::start() {
        SDL_Init(SDL_INIT_VIDEO);
        atexit(SDL_Quit);
        SDL_WM_SetCaption("SDL GL Application", NULL);
        SDL_SetVideoMode(height, width, 32, SDL_OPENGL);
        SDL_WarpMouse(height / 2, width / 2);

        // Set color and depth clear value
        glClearDepth(1.f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.f);

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
		
		try {
			loop();
		} catch (std::exception const & e) {
			std::cout << "Exception !: " << e.what() << "\n";
		}
		
		SDL_Quit();
	}
	
	void Application::draw() {
		glPolygonMode(GL_FRONT_AND_BACK, mode);

		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Apply some transformations
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		camera.render();

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_blue.get());
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_reflection.get());
		glMateriali(GL_FRONT, GL_SHININESS, 192);

		renderer.render(ngn::Vector3D::zero(), basis);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(xyPlaneMeshColor.getR(), xyPlaneMeshColor.getG(), xyPlaneMeshColor.getB());		
		renderer.render(xyPlaneMesh);
		
		glColor3f(0.82, 0.41, 0.12);
		renderer.render(floor);
		
		for (int unsigned i = 0; i < sweepers->size(); ++i) {
			SharedPtrSmartMineSweeper sweeper = sweepers->operator [](i);
			renderSweeper(sweeper);
		}
		
		glColor3f(0.0f, 0.0f, 1.0f);
		
		for (int unsigned i = 0; i < mines->size(); ++i) {
			SharedPtrMine mine = mines->operator [](i);
			renderMine(mine);
		}
		
		SDL_GL_SwapBuffers();
		
		if (warp_mouse) {
			SDL_WarpMouse(640, 480);
			warp_mouse = false;
		}
	}
	
	void Application::drawBoundingSphereOfSweeper(SharedPtrSmartMineSweeper const & sweeper) const {
		ngn::Sphere const & boundingSphere = sweeper->getBoundingSphere();
		renderer.render(
			boundingSphere.getCenter(), 
			Matrix3D::identity(), 
			*sweeperBoundingSphereMesh
		);		
	}
	
	//draw the direction to the closest mine scaled by a factor of 25.0
	void Application::drawDirectionToClosestMineFromSweeper(SharedPtrSmartMineSweeper const & sweeper) const {
		OrientedBox3D * boundingBox;
		boundingBox = static_cast<OrientedBox3D*>(&(*sweeper->getBoundingVolume()));
		
		if (sweeper->getClosestMineDirection() == nullptr) {
			std::string message = "UnsupportedOperationException:\n";
			message += "Application::renderSweeper(";
			message += "SharedPtrSmartMineSweeper const & sweeper) const:\n";
			message += "sweeper->getClosestMineDirection() == nullptr";
			throw UnsupportedOperationException(message);
		}
		
		Vector3D closestMineDirection = *(sweeper->getClosestMineDirection());
		Vector3D pWorld = 
			Vector3D::add(
				boundingBox->getCenter(), 
				Vector3D::mult(closestMineDirection, parameters.getSweeperWheelBase())
			);
		
		glBegin(GL_LINES);
			glVertex3f(
				boundingBox->getCenter().getX(), 
				boundingBox->getCenter().getY(), 
				boundingBox->getCenter().getZ()
			);
			glVertex3f(pWorld.getX(), pWorld.getY(), pWorld.getZ());
		glEnd();		
	}
	
	void Application::drawSweeper(SharedPtrSmartMineSweeper const & sweeper) const {
		OrientedBox3D * boundingBox;
		boundingBox = static_cast<OrientedBox3D*>(&(*sweeper->getBoundingVolume()));
		RGBColor sColor = sweeper->getColor();
		glColor3f(sColor.getR(), sColor.getG(), sColor.getB());
		renderer.render(*boundingBox);
		
		//draw boxes that form the shape of the tank
		for (int unsigned j = 0; j < sweeperGeometries.size(); ++j) {
			OrientedBox3D geometry = sweeperGeometries.operator [](j);
			Vector3D center = 
				Vector3D::add(
					boundingBox->getCenter(), 
					boundingBox->getOrientation().mult(geometry.getCenter())
				);
			Matrix3D orient(boundingBox->getOrientation());
			OrientedBox3D tmp(center, orient, geometry.getHalfExtents());
			renderer.render(tmp);
		}		
	}
	
	void Application::initializeFloor() {
		Real depth = 30.0;
		Vector3D center = 
			Vector3D::mult(
				Vector3D::add(parameters.getWorldOrigin(), parameters.getWorldExtents()),
				(Real)0.5
			);
		center.setZ(-depth / 2.0 - 1.0);
		Matrix3D orientation = Matrix3D::identity();
		Vector3D halfExtents = Vector3D::mult(parameters.getWorldExtents(), (Real)0.5);
		halfExtents.setZ(-depth / 2.0);
		floor = OrientedBox3D(center, orientation, halfExtents);		
	}
	
	void Application::initializeSweeperGeometries() {
		ngn::Real halfBase = parameters.getSweeperWheelBase() / 2.0;
		ngn::Real halfWidth = parameters.getSweeperWidth() / 2.0;
		ngn::Real halfHeight = parameters.getSweeperHeight() / 2.0;
		OrientedBox3D box1(
			Vector3D::zero(), 
			Matrix3D::identity(), 
			Vector3D(halfBase, halfWidth, halfHeight)
		);
		sweeperGeometries.push_back(box1);
		ngn::Real xPos = parameters.getSweeperWheelBase() / -16.0;
		ngn::Real xHalfExtent2 = 5.0 * parameters.getSweeperWheelBase() / 16.0; 
		ngn::Real zHalfExtent2 = 3.0 * parameters.getSweeperHeight() / 8.0;
		OrientedBox3D box2(
			Vector3D(xPos, 0.0, halfHeight + zHalfExtent2),
			Matrix3D::identity(),
			Vector3D(xHalfExtent2, halfWidth / 2.0, zHalfExtent2)
		);
		sweeperGeometries.push_back(box2);
		OrientedBox3D box3(
			Vector3D(halfBase, 0.0, halfHeight + zHalfExtent2),
			Matrix3D::identity(),
			Vector3D(halfBase / 2.0, halfHeight / 2.0, halfHeight / 4.0)
		);
		sweeperGeometries.push_back(box3);
	}
	
	void Application::initializeSweepersAndMines() {
		std::shared_ptr<Grid3D> grid = std::make_shared<Grid3D>(
			parameters.getWorldOrigin(),
			parameters.getWorldExtents(),
			Partitions(
				parameters.getNumberOfRowsOfSpacePartition(),
				parameters.getNumberOfColumnsOfSpacePartition(),
				1
			)
		);
		RandomGeneratorOfSweepersAndMines generator(grid, parameters);
		std::pair<
			std::shared_ptr<std::vector<smrtsw::SharedPtrSmartMineSweeper>>, 
			std::shared_ptr<std::vector<smrtsw::SharedPtrMine>>
		> pairOfVectors;
		pairOfVectors = generator.generateSweepersAndMines();
		sweepers = pairOfVectors.first;
		mines = pairOfVectors.second;
		
		std::cout << "mines->size() = " << mines->size() << "\n";		
	}
	
	void Application::loop() {
		startSimulation();
		
		while (on) {
			Real currentTime = SDL_GetTicks();
			Real deltaTime = 0;
			
			if (shouldRunOnline) {
				std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMillis));
				deltaTime = (SDL_GetTicks() - currentTime) / 1000.0;
			} else {
				deltaTime = frameTime;
			}
			
			simulation.func2(deltaTime);
			
			if (shouldDraw) {
				draw();
			}
			
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
		}
	}
	
	void Application::renderMine(SharedPtrMine const & mine) const {
		renderer.render(mine->getPosition(), Matrix3D::identity(), *mineMesh);
	}
	
	void Application::renderSweeper(SharedPtrSmartMineSweeper const & sweeper) const {
		if (sweeper == nullptr) {
			std::string message = "IllegalArgumentException:\n";
			message += "Application::renderSweeper(";
			message += "SharedPtrSmartMineSweeper const & sweeper) const:\n";
			message += "sweeper == nullptr";
			throw IllegalArgumentException(message);
		}
		
		drawSweeper(sweeper);
		drawDirectionToClosestMineFromSweeper(sweeper);
		
		if (shouldDrawBoundingSpheres) {
			drawBoundingSphereOfSweeper(sweeper);
		}
	}
	
	void Application::startSimulation() {
		shouldDraw = true;
		shouldRunOnline = false;
		simulation.setOnLine(shouldRunOnline);
	}
	
	void Application::onSDLMouseMotion(SDL_Event & event) {
		dx = 5.0 * -event.motion.yrel * ngn::Math<ngn::Real>::PI / (2.0 * width);
		dy = 5.0 * -event.motion.xrel * ngn::Math<ngn::Real>::PI / (2.0 * height);
		camera.rotateX(dx);
		camera.rotateY(dy);
	}
	
	void Application::onSDLQuit(SDL_Event & event) {
		on = false;
	}
	
	void Application::onSDLKeyDown(SDL_Event & event) {
		switch (event.key.keysym.sym) {
			
			case SDLK_ESCAPE:
				onEscapeKey(event);
				break;
				
			case SDLK_SPACE:
				onSpaceKey(event);
				break;

			case SDLK_a:
				onAKey(event);
				break;
				
			case SDLK_b:
				onBKey(event);
				break;
				
			case SDLK_c:
				onCKey(event);
				break;
			
			case SDLK_d:
				onDKey(event);
				break;
				
			case SDLK_f:
				onFKey(event);
				break;

			case SDLK_h:
				onHKey(event);
				break;
				
			case SDLK_m:
				onMKey(event);
				break;

			case SDLK_n:
				onNKey(event);
				break;

			case SDLK_p:
				onPKey(event);
				break;
				
			case SDLK_r:
				onRKey(event);
				break;

			case SDLK_s:
				onSKey(event);
				break;
			
			case SDLK_v:
				onVKey(event);
				break;
				
			case SDLK_x:
				onXKey(event);
				break;
				
			case SDLK_y:
				onYKey(event);
				break;
				
			case SDLK_w:
				onWKey(event);
				break;

			default:
				break;
		}
	}
		
	void Application::onSpaceKey(SDL_Event & event) { 
		if (mode == GL_FILL) {
			mode = GL_LINE;
		} else {
			if (mode == GL_LINE) {
				mode = GL_FILL;
			}
		}		
	}
	
	void Application::onEscapeKey(SDL_Event & event) { 
		on = false;
	}
	
	void Application::onAKey(SDL_Event & event) {
		camera.rotateY(increment * Math<Real>::PI / 1800);
	}
	
	void Application::onBKey(SDL_Event & event) {
		shouldDrawBoundingSpheres = !shouldDrawBoundingSpheres;
	}
	
	void Application::onCKey(SDL_Event & event) {
		camera.strafeRight(-increment);
	}
	
	void Application::onDKey(SDL_Event & event) {
		camera.rotateY(-increment * Math<Real>::PI / 1800);
	}
	
	void Application::onFKey(SDL_Event & event) {
		camera.moveUpward(-increment);
	}
	
	void Application::onHKey(SDL_Event & event) {
		shouldDraw = !shouldDraw;
		std::cout << (shouldDraw ? "R": "Not r") << "endering\n"; 
	}
	
	void Application::onMKey(SDL_Event & event) {
		camera.rotateZ(-increment * Math<Real>::PI / 1800);
	}
	
	void Application::onNKey(SDL_Event & event) {
		camera.rotateZ(increment * Math<Real>::PI / 1800);
	}
	
	void Application::onPKey(SDL_Event & event) {
		shouldRunOnline = !shouldRunOnline;
		//shouldDraw = !shouldDraw;
		simulation.setOnLine(!simulation.isOnLine());
		std::cout << "###Simulation running ";
		std::cout << (simulation.isOnLine() ? "online": "offline") << "\n";
	}
	
	void Application::onRKey(SDL_Event & event) {
		camera.moveUpward(increment);
	}
	
	void Application::onSKey(SDL_Event & event) {
		camera.moveForward(increment);
	}
	
	void Application::onVKey(SDL_Event & event) {
		camera.strafeRight(increment);
	}
	
	void Application::onXKey(SDL_Event & event) {
		camera.rotateX(increment * Math<Real>::PI / 1800);
	}
	
	void Application::onYKey(SDL_Event & event) {
		camera.rotateX(-increment * Math<Real>::PI / 1800);
	}
	
	void Application::onWKey(SDL_Event & event) {
		camera.moveForward(-increment);
	}
	
	void Application::initializeXYPlaneMesh() {
		ngn::Partitions partitions(
			parameters.getNumberOfRowsOfSpacePartition(),
			parameters.getNumberOfColumnsOfSpacePartition(),
			1
		);
		std::shared_ptr<std::vector<ngn::Vector3D>> vertices(new std::vector<ngn::Vector3D>());
		std::shared_ptr<std::vector<ngn::Line>> lines(new std::vector<ngn::Line>());
		ngn::Real minX = parameters.getWorldOrigin().getX();
		ngn::Real maxX = minX + parameters.getWorldExtents().getX();
		ngn::Real minY = parameters.getWorldOrigin().getY();
		ngn::Real maxY = minY + parameters.getWorldExtents().getY();
		ngn::Real minZ = parameters.getWorldOrigin().getZ();
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
		
		xyPlaneMesh.setPoints(vertices);
		xyPlaneMesh.setLines(lines);
	}
}
