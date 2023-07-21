#ifndef SELECTOR_H
#define SELECTOR_H

#include <boost/shared_ptr.hpp>
#include <iosfwd>
#include "Population.h"

namespace ai {

	class Selector {
	public:
		virtual void setPopulation(Population const & chrs) = 0;
		virtual SharedPtrChromosome select() = 0;
		virtual void print(std::ostream & out) const = 0;
	};	
	
	std::ostream & operator<<(std::ostream & out, Selector const & selector);
	
	typedef boost::shared_ptr<Selector> SelectorSmartPtr;
}

#endif // SELECTOR_H