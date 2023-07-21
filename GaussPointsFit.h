#ifndef GAUSS_POINTS_FIT_H
#define GAUSS_POINTS_FIT_H

#include <cassert>
#include <vector>
#include "Matrix3D.h"
#include "Vector3D.h"

namespace ngn {
    
	class Matrix3D;
    class Vector3D;

    class GaussPointsFit {
    public:
        class Result {
        public:
            Result();
            Result(Vector3D const & mean, Matrix3D const & naturalAxes, Vector3D const & halfExtents) ;
            Vector3D const & getMeanPoint() const;
            Matrix3D const & getNaturalAxes() const;
            Vector3D const & getHalfExtents() const;
			
        private:
            Vector3D meanPoint_;
            Matrix3D naturalAxes_;
            Vector3D halfExtents_;
        };

        GaussPointsFit();

        Result operator()(std::vector<Vector3D> const & vertices)const;
        Result operator()(std::vector<Vector3D> const & vertices, std::vector<int unsigned> const & vertex_indices)const;
    };

    ////////////////////////////////////////////////////////////////////////

}

#endif // GAUSS_POINTS_FIT_H