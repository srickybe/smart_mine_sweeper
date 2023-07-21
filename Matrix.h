#ifndef MATRIX_H
#define MATRIX_H

#include <iosfwd>
#include <vector>
#include "Real.h"

namespace ngn {

	class Range;
	class Vector;
	class Matrix {

	public:
		Matrix();
		Matrix(int nRows, int nCols);
		Matrix(std::vector<std::vector<Real>> const & entries, int nRows, int nCols);
		Matrix(Matrix const & rhs);

		static Matrix random(int nRows, int nCols, Range const & range);
		static Matrix zero(int nRows, int nCols);

		bool equals(Matrix const & rhs, Real eps) const;
		Real getElem(int i, int j) const;
		int getNRows() const;
		int getNCols() const;
		void setElem(int i, int j, Real val);
		Matrix mult(Matrix const & rhs) const;
		Vector mult(Vector const & rhs) const;
		static void test();
		
	private:
		int nRows;
		int nCols;
		std::vector<std::vector<Real>> elems;
	};
	
	std::ostream & operator<<(std::ostream & out, Matrix const & mat);
}

#endif // MATRIX_H