#include "World.h"
#include "Line.h"
#include "Mesh.h"

namespace smrtsw {
	
	World::World() {
		
	}
	
	World::World(ngn::Vector3D const & origin, ngn::Vector3D const & extents) {
		this->origin = origin;
		this->extents = extents;
	}

	bool World::containsPosition(ngn::Vector3D const & position) const {
		ngn::Vector3D delta = ngn::Vector3D::sub(position, getOrigin());

		return delta.getX() <= extents.getX() && delta.getX() >= 0.0
				&& delta.getY() <= extents.getY() && delta.getY() >= 0.0
				&& delta.getZ() <= extents.getZ() && delta.getZ() >= 0.0;
	}
	
	ngn::Vector3D const & World::getOrigin() const {
		return origin;
	}

	ngn::Vector3D const & World::getExtents() const {
		return extents;
	}

	ngn::Vector3D World::getLowerLeftCorner() const {
		return ngn::Vector3D(getMinX(), getMinY(), 0.0);
	}
	
	ngn::Vector3D World::getUpperLeftCorner() const {
		return ngn::Vector3D(getMinX(), getMaxY(), 0.0);
	}
	
	ngn::Vector3D World::getLowerRightCorner() const {
		return ngn::Vector3D(getMaxX(), getMinY(), 0.0);
	}
	
	ngn::Vector3D World::getUpperRightCorner() const {
		return ngn::Vector3D(getMaxX(), getMaxY(), 0.0);
	}
		
	ngn::Real World::getMaxX() const {
		return getOrigin().getX() + getExtents().getX();
	}

	ngn::Real World::getMinX() const {
		return getOrigin().getX();
	}

	ngn::Real World::getMaxY() const {
		return getOrigin().getY() + getExtents().getY();
	}

	ngn::Real World::getMinY() const {
		return getOrigin().getY();
	}

	ngn::Real World::getMaxZ() const {
		return getOrigin().getZ() + getExtents().getZ();
	}
	
	ngn::Real World::getMinZ() const {
		return getOrigin().getZ();
	}
	
	std::shared_ptr<ngn::Mesh> World::getMesh(ngn::Partitions const & partitions) const {
		std::shared_ptr<std::vector<ngn::Vector3D>> vertices(new std::vector<ngn::Vector3D>());
		std::shared_ptr<std::vector<ngn::Line>> lines(new std::vector<ngn::Line>());
		ngn::Real xCoord = getMinX();
		
		for (int i = 0; i <= partitions.getXAxisPartitions(); ++i) {
			vertices->push_back(ngn::Vector3D(xCoord, getMinY(), getMinZ()));
			vertices->push_back(ngn::Vector3D(xCoord, getMaxY(), getMinZ()));
			lines->push_back(ngn::Line(vertices->size() - 2, vertices->size() - 1));
			xCoord += (getExtents().getX() / partitions.getXAxisPartitions());
		}
		
		ngn::Real yCoord = getMinY();
		
		for (int i = 0; i <= partitions.getYAxisPartitions(); ++i) {
			vertices->push_back(ngn::Vector3D(getMinX(), yCoord, getMinZ()));
			vertices->push_back(ngn::Vector3D(getMaxX(), yCoord, getMinZ()));
			lines->push_back(ngn::Line(vertices->size() - 2, vertices->size() - 1));
			yCoord += (getExtents().getY() / partitions.getYAxisPartitions());
		}
		
		std::shared_ptr<ngn::Mesh> mesh(new ngn::Mesh());
		mesh->setPoints(vertices);
		mesh->setLines(lines);
		
		return mesh;
	}
	
	ngn::Vector3D World::randomPosition() const {
		ngn::Real dx = (ngn::Real) (util::Rand<ngn::Real>::getInstance().next() * getExtents().getX());
		ngn::Real x = (ngn::Real) getOrigin().getX() + dx;    
		ngn::Real dy = (ngn::Real) (util::Rand<ngn::Real>::getInstance().next() * getExtents().getY());
		ngn::Real y = (ngn::Real) getOrigin().getY() + dy;
		ngn::Real dz = (ngn::Real) (util::Rand<ngn::Real>::getInstance().next() * getExtents().getZ());
		ngn::Real z = (ngn::Real) getOrigin().getZ() + dz;

		return ngn::Vector3D(x, y, z);
	}

	
	void World::print(std::ostream & out) const {
		out << "World{" << "origin=" << origin << ", extents=" << extents << "}";
	}

	void World::test() {
		ngn::Vector3D origin(0, 0, 0);
		ngn::Vector3D extents(100, 100, 100);
		World world(origin, extents);
		std::cout << "world =\n" << world << "\n";
	}
	
	std::ostream & operator<<(std::ostream & out, World const & world) {
		world.print(out);
		
		return out;
	}
}