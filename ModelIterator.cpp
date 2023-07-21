#include "ModelIterator.h"

namespace ngn {
	
	ModelIterator::ModelIterator()
    : iter_() {
    }

	ModelIterator::ModelIterator(std::map<std::string, std::shared_ptr<Mesh>>::iterator const & iter): iter_(iter) {
    }
	
	bool const ModelIterator::operator!=(ModelIterator const & iterator) const {
        return this->iter_ != iterator.iter_;
    }

	ModelIterator & ModelIterator::operator++() {
        ++iter_;
        return *this;
    }

	ModelIterator & ModelIterator::operator--() {
        --iter_;
        return *this;
    }

	std::shared_ptr< Mesh >& ModelIterator::operator*() {
        return iter_->second;
    }

     std::shared_ptr< Mesh >& ModelIterator::operator->() {
        return iter_->second;
    }
}