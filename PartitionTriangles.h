#ifndef PARTITION_TRIANGLES_H
#define PARTITION_TRIANGLES_H

#include <boost/scoped_array.hpp>
#include <memory>
#include <vector>
#include "OrientedBox3D.h"
#include "Vector3D.h"

namespace ngn {

    class PartitionTriangles {
    public:

        class Result {
        public:

            Result(
				std::shared_ptr<std::vector<int unsigned>> const & leftSideTriples,
				std::shared_ptr<std::vector<int unsigned>> const & rightSideTriples,
				bool partitioned
			) {
                leftSideTriples_ = leftSideTriples;
                rightSideTriples_ = rightSideTriples;
                partitioned_ = partitioned;
            }

            std::shared_ptr<std::vector<int unsigned>> const & getLeftSideTriples() const {
                return leftSideTriples_;
            }

            std::shared_ptr<std::vector<int unsigned>> const & getRightSideTriples() const {
                return rightSideTriples_;
            }

            bool partitioned() const {
                return partitioned_;
            }

        private:
            std::shared_ptr<std::vector<int unsigned>> leftSideTriples_;
            std::shared_ptr<std::vector<int unsigned>> rightSideTriples_;
            bool partitioned_;
        };

        PartitionTriangles();

        Result operator()
        (
			OrientedBox3D const & box, //box
			std::vector<Vector3D> const & centers
		)
        const;

        Result operator()
        (
			OrientedBox3D const & box, //box
			std::vector<Vector3D> const & centers, //centers of the tirnagles
			std::vector<int unsigned> const & triple_indices
		)
        const;

    private:
    };

    ////////////////////////////////////////////////////////////////////////

}

#endif // PARTITION_TRIANGLES_H