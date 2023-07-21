#include "Mine.h"
#include <iostream>
#include "IllegalArgumentException.h"
#include "MeshBuilder.h"
#include "Real.h"
#include "Sphere.h"

namespace smrtsw {
	
	int Mine::NUMBER_OF_MINES = 0;
	//int Mine::numberOfPointsOfCircle = 20;
	
	std::shared_ptr<ngn::Mesh> Mine::MESH = ngn::MeshBuilder::unitSphereMesh(3);
	
	int Mine::getNumberOfMines() {
		return NUMBER_OF_MINES;
	}
	
	void Mine::incrementNumberOfMines() {
		++NUMBER_OF_MINES;
	}
	
	ngn::Matrix3D const Mine::ORIENTATION = ngn::Matrix3D::identity();
	
	Mine::Mine() :
		ID(Mine::getNumberOfMines()),
		position(ngn::Vector3D::zero()),
		boundingVolume(new ngn::Sphere(ngn::Vector3D::zero(), (ngn::Real)0.0)),
		movable(false)
	{
		Mine::incrementNumberOfMines();
	}
	
	Mine::Mine(ngn::Vector3D const & pos, ngn::SharedPtrIntersectable const & bV) :
		ID(Mine::getNumberOfMines()),
		position(pos),
		boundingVolume(bV),
		movable(false)
	{
		Mine::incrementNumberOfMines();
		
		if (!getPosition().equalsWithTol(boundingVolume->getPosition(), (ngn::Real)1.0e-6)) {
			throw IllegalArgumentException("Position of mine different from position of bounding volume!!!");
		}
	}
	
	/*void draw(Graphics g) {
		getBoundingVolume().draw(g);
		String blockID = "" + getBlock().getRow() + ":" + getBlock().getColumn();
		g.drawString(blockID, (int) position.getX() - 5, (int) position.getY() - 5);
	}*/
	
	int Mine::getID() const {
		return ID;
	}
	
	ngn::Vector3D const & Mine::getPosition() const {
		return this->position;
	}

	ngn::Matrix3D const & Mine::getOrientation() const {
		return Mine::ORIENTATION;
	}
	
	ngn::Sphere const & Mine::getBoundingSphere() const {
		return *(std::dynamic_pointer_cast<ngn::Sphere>(this->boundingVolume));
	}
	
	ngn::SharedPtrIntersectable const &  Mine::getBoundingVolume() const {
		return this->boundingVolume;
	}

	std::shared_ptr<ngn::Mesh> const & Mine::getMesh() const {
		return Mine::MESH;
	}
	 
	void Mine::setBoundingSphere(ngn::Sphere const & sphere) {
		this->boundingVolume = ngn::SharedPtrIntersectable(new ngn::Sphere(sphere));
	}
	
	void Mine::setMovable(bool mvbl) {
		this->movable = mvbl;
	}
		
	void Mine::setPosition(ngn::Vector3D const & pos) {
		this->position = pos;
		this->boundingVolume->setPosition(pos);
	}
	
	
	void Mine::print(std::ostream & out) const {
		out << "Mine{" 
			<< "\nposition=" << position 
			<< ",\nboundingVolume=" << *boundingVolume 
			<< "\n}";
	}

	
	bool Mine::isMovable() const {
		return false;
	}
	
	/*std::ostream & operator<<(std::ostream & out, Mine const & mine) {
		mine.print(out);
		
		return out;
	}*/
}