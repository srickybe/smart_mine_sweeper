#include "GraphicObject.h"

namespace ngn {
	
	GraphicObject::GraphicObject() :
		mesh_(),
		position_(),
		orientation_()
	{
		
	}
	
	GraphicObject::GraphicObject(
		std::shared_ptr<Mesh> const & mesh,
		Vector3D const & position,
		Matrix3D const & orientation
	) :
		mesh_(mesh),
		position_(position),
		orientation_(orientation)
	{
		
	}
	
	std::shared_ptr<Mesh> const & GraphicObject::getMesh() const {
		return mesh_;
	}
	
	Matrix3D const & GraphicObject::getOrientation() const {
		return orientation_;
	}
	
	Vector3D const & GraphicObject::getPosition() const {
		return position_;
	}
	
	void GraphicObject::setMesh(std::shared_ptr<Mesh> const & mesh) {
		mesh_ = mesh;
	}
	
	void GraphicObject::setOrientation(Matrix3D const & orientation) {
		orientation_ = orientation;
	}
	
	void GraphicObject::setPosition(Vector3D const & position) {
		position_ = position;
	}
}