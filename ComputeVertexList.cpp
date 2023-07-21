#include "ComputeVertexList.h"

#include <cassert>
#include <set>


namespace ngn {

    ComputeVertexList::ComputeVertexList() {
    }

    std::shared_ptr<std::vector<int unsigned>> 
    ComputeVertexList::operator()(
		std::vector<Triangle> const & triples, 
		std::vector<int unsigned> const & triple_indices
	)
    const {
        assert(!triples.empty());
        assert(!triple_indices.empty());
        assert(triple_indices.size() <= triples.size());

        std::set< int unsigned > vertex_index_set;
        int unsigned vertex_index;

        for (int unsigned i = 0; i < triple_indices.size(); ++i) {
            for (int unsigned j = 0; j < 3; ++j) {
                vertex_index = (triples.at(triple_indices.at(i))).getVertexIndex(j);
                vertex_index_set.insert(vertex_index);
            }
        }

        assert(!(vertex_index_set.empty()));
        std::shared_ptr<std::vector<int unsigned>> vertex_indices(new std::vector<int unsigned>());
        vertex_indices->assign(vertex_index_set.begin(), vertex_index_set.end());
        
        return vertex_indices;
    }
}

