#ifndef MODEL_ITERATOR_H
#define MODEL_ITERATOR_H

#include "Mesh.h"
#include <map>
#include <memory>

namespace ngn {

    
    class ModelIterator {
    public:
        ModelIterator();
		ModelIterator(std::map<std::string, std::shared_ptr<Mesh>>::iterator const & iter);
		
        bool const operator!=(ModelIterator const & iterator)const;
        ModelIterator & operator++();
        ModelIterator & operator--();
        std::shared_ptr<Mesh> & operator*();
        std::shared_ptr<Mesh> & operator->();

    private:
        std::map<std::string, std::shared_ptr<Mesh>>::iterator iter_;
    };

    ////////////////////////////////////////////////////////////////////////
}

#endif // MODEL_ITERATOR_H