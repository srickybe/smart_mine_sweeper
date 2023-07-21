#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include "Mesh.h"
#include "Partitions.h"
#include "Rand.h"
#include "Real.h"
#include "Vector3D.h"

namespace smrtsw {
	
	class World;
	std::ostream & operator<<(std::ostream & out, World const & world);
	
	class World {
    private:
		ngn::Vector3D origin;
		ngn::Vector3D extents;

    public:
		World();
		World(ngn::Vector3D const & origin, ngn::Vector3D const & extents);
		
		bool containsPosition(ngn::Vector3D const & position) const;
		ngn::Vector3D const & getOrigin() const;
		ngn::Vector3D const & getExtents() const;
		ngn::Vector3D getLowerLeftCorner() const;
		ngn::Vector3D getUpperLeftCorner() const;
		ngn::Vector3D getLowerRightCorner() const;
		ngn::Vector3D getUpperRightCorner() const;
		ngn::Real getMaxX() const;
		ngn::Real getMinX() const;
		ngn::Real getMaxY() const;
		ngn::Real getMinY() const;
		ngn::Real getMaxZ() const;
		ngn::Real getMinZ() const;
		std::shared_ptr<ngn::Mesh> getMesh(ngn::Partitions const & partitions) const;
		ngn::Vector3D randomPosition() const;
		void print(std::ostream & out) const;
		static void test();
	};
	
	std::ostream & operator<<(std::ostream & out, World const & world);
}

#endif // WORLD_H