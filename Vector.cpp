#include "Vector.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include "Rand.h"
#include "Range.h"

namespace ngn {
	
	Vector::Vector() : elems_() 
	{
	}

	Vector::Vector(std::vector<Real> const & elems) 
	: elems_(elems) 
	{
	}

	Vector::Vector(int length) 
	: elems_(length, (Real)0.0) 
	{
	}

	Vector::Vector(Vector const & rhs) 
	: elems_(rhs.elems_) {
	}

	Vector Vector::zero(int length) 
	{
		return Vector(length);
		
	}
	
	Vector Vector::random(int nElems, Range const & range) 
	{
		Vector res(nElems);

		for (int i = 0; i < nElems; ++i) {
			Real rnd = util::Rand<Real>::getInstance().next(range.getMin(), range.getMax());
			res.setElem(i, rnd);
		}

		return res;
	}

	bool Vector::equals(Vector const & rhs, Real eps) const
	{
		if (this == &rhs) {
			return true;
		}

		if (length() != rhs.length()) {
			return false;
		}

		for (int i = 0; i < length(); ++i) {
			if (std::abs(getElem(i) - rhs.getElem(i)) > eps) {
				return false;
			}
		}

		return true;
	}

	Real Vector::getElem(int i) const
	{
		return elems_[i];
	}

	bool Vector::hasNaNElement() const {
		for (int i = 0; i < length(); ++i) 
		{
			if (std::isnan(getElem(i))) 
			{
				return true;
			}
		}
		
		return false;
	}
	
	void Vector::setElem(int i, Real elem) 
	{
		elems_[i] = elem;
	}

	int Vector::length() const {
		return elems_.size();
	}

	Vector Vector::add(Vector const & rhs) 
	{
		Vector res(length());

		for (int i = 0; i < res.length(); ++i) 
		{
			res.setElem(i, this->getElem(i) + rhs.getElem(i));
		}

		return res;
	}

	Vector Vector::sub(Vector const & rhs) 
	{
		Vector res(length());

		for (int i = 0; i < res.length(); ++i) 
		{
			res.setElem(i, this->getElem(i) - rhs.getElem(i));
		}

		return res;
	}
	
    std::ostream & operator<<(std::ostream & out, Vector const & vec) {
        for (int i = 0; i < vec.length(); ++i) {
			out << std::right << std::setw(12) << std::setprecision(6);
			out << vec.getElem(i) << "\n";
		}

        return out;
    }
}