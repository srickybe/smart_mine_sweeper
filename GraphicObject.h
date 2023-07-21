#ifndef GRAPHIC_OBJECT_H
#define GRAPHIC_OBJECT_H

#include <memory>
#include "Matrix3D.h"
#include "Mesh.h"
#include "Vector3D.h"

namespace ngn {
	
	class GraphicObject {
	public:
		GraphicObject();
		GraphicObject(
			std::shared_ptr<Mesh> const & mesh,
			Vector3D const & position,
			Matrix3D const & orientation
		);
		
		std::shared_ptr<Mesh> const & getMesh() const;
		Matrix3D const & getOrientation() const;
		Vector3D const & getPosition() const;
		
		void setMesh(std::shared_ptr<Mesh> const & mesh);
		void setOrientation(Matrix3D const & orientation);
		void setPosition(Vector3D const & position);
		
	private:
		std::shared_ptr<Mesh> mesh_;
		Vector3D position_;
		Matrix3D orientation_;
	};
	
	typedef std::shared_ptr<GraphicObject> SharedPtrGraphicObject;
}

#endif // GRAPHIC_OBJECT_H