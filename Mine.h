#ifndef MINE_H
#define MINE_H

#include <iosfwd>
#include <memory>
#include "Intersectable.h"
#include "Matrix3D.h"
#include "Mesh.h"
#include "PhysicObject3D.h"
#include "Vector3D.h"

namespace smrtsw {
	
	class Sphere; 
	
	class Mine: public ngn::PhysicObject3D {
	public:
		Mine();
		Mine(ngn::Vector3D const & pos, ngn::SharedPtrIntersectable const & bV);
		int getID() const;
		ngn::Sphere const & getBoundingSphere() const;
		ngn::SharedPtrIntersectable const & getBoundingVolume() const;
		std::shared_ptr<ngn::Mesh> const & getMesh() const;
		ngn::Vector3D const & getPosition() const;
		ngn::Matrix3D const & getOrientation() const;
		bool isMovable() const;
		void print(std::ostream & out) const;
		void setBoundingSphere(ngn::Sphere const & sphere);
		void setMovable(bool movable);
		void setPosition(ngn::Vector3D const & pos);
		
	private:
		int ID;
		ngn::Vector3D position;
		ngn::SharedPtrIntersectable boundingVolume;
		bool movable;
		
		static int NUMBER_OF_MINES;
		//static int numberOfPointsOfCircle;
		static std::shared_ptr<ngn::Mesh> MESH;
		static int getNumberOfMines();
		static void incrementNumberOfMines();
		static ngn::Matrix3D const ORIENTATION;
	};
	
	//std::ostream & operator<<(std::ostream & out, Mine const & mine);
	typedef std::shared_ptr<Mine> SharedPtrMine;
}

#endif // MINE_H