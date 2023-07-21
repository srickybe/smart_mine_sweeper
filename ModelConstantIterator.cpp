#include "ModelConstantIterator.h"
#include "Mesh.h"

namespace ngn {
	
    ModelConstantIterator::ModelConstantIterator()
    : iter_() {
    }

    ModelConstantIterator::ModelConstantIterator(
		typename map_t::const_iterator const & iter
	)
    : iter_(iter) {
    }

    
    bool const ModelConstantIterator::operator!=
    (
		ModelConstantIterator const & iterator
	)const {
        return this->iter_ != iterator.iter_;
    }

    
    ModelConstantIterator & ModelConstantIterator::operator++() {
        ++iter_;
        return *this;
    }

    
    ModelConstantIterator & ModelConstantIterator::operator--() {
        --iter_;
        return *this;
    }

    
    std::shared_ptr< Mesh > const & ModelConstantIterator::operator*()const {
        return iter_->second;
    }

    
    std::shared_ptr< Mesh > const & ModelConstantIterator::operator->()const {
        return iter_->second;
    }		
}