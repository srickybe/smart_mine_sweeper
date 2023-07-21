#ifndef VECTOR_H
#define VECTOR_H

#include <iosfwd>
#include <vector>
#include "Real.h"

namespace ngn {
	
	class Range;
	
	class Vector {
	public:
		Vector();
		Vector(std::vector<Real> const & elems);
		Vector(int length);
		Vector(Vector const & rhs);

		static Vector zero(int nElems);
		static Vector random(int nElems, Range const & range);

		bool equals(Vector const & rhs, Real eps) const;
		Real getElem(int i) const;
		bool hasNaNElement() const;
		void setElem(int i, Real elem);
		int length() const;
		Vector add(Vector const & rhs);
		Vector sub(Vector const & rhs);
		
	private: 
		std::vector<Real> elems_;
	};
	
	std::ostream & operator<<(std::ostream & out, Vector const & vec);
}

#endif // VECTOR_H