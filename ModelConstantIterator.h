#ifndef MODEL_CONSTANT_ITERATOR_H
#define MODEL_CONSTANT_ITERATOR_H

#include <map>
#include <memory>

namespace ngn {

	class Mesh;
	
    class ModelConstantIterator {
    public:
        typedef Mesh mesh_t;
        typedef std::shared_ptr< mesh_t > mesh_ptr_t;
        typedef std::pair< const std::string, mesh_ptr_t > pair_t;

        typedef std::map
        <
        std::string,
        mesh_ptr_t,
        std::less< std::string >,
        std::allocator< pair_t >
        >
        map_t;

        ModelConstantIterator();
        ModelConstantIterator(typename map_t::const_iterator const & iter);
        bool const operator!=(ModelConstantIterator const & iterator)const;
        ModelConstantIterator & operator++();
        ModelConstantIterator & operator--();
        mesh_ptr_t const & operator*()const;
        mesh_ptr_t const & operator->()const;

    private:
        typename map_t::const_iterator iter_;
    };

    ////////////////////////////////////////////////////////////////////////
}

#endif // MODEL_CONSTANT_ITERATOR_H