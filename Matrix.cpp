#include "Matrix.h"
#include <iomanip>
#include <iostream>
#include "Math.h"
#include "Rand.h"
#include "Range.h"
#include "Vector.h"

namespace ngn {
	
	Matrix::Matrix() 
	: nRows(0),
	nCols(0),
	elems()
	{
	}
	
	Matrix::Matrix(int nRows, int nCols) 
	: elems()
	{
		this->nRows = nRows;
		this->nCols = nCols;

		for (int i = 0; i < this->nRows; ++i) {
			this->elems.push_back(std::vector<Real>());

			for (int j = 0; j < this->nCols; ++j) {
				this->elems[i].push_back(0.0);
			}
		}
	}

	Matrix::Matrix(std::vector<std::vector<Real>> const & entries, int nRows, int nCols) {
		Matrix(nRows, nCols);

		for (int i = 0; i < this->getNRows(); ++i) {
			for (int j = 0; j < this->getNCols(); ++j) {
				this->setElem(i, j, entries[i][j]);
			}
		}
	}

	Matrix::Matrix(Matrix const & rhs) 
	: nRows(rhs.nRows),
	nCols(rhs.nCols),
	elems(rhs.elems)
	{
		//Matrix(rhs.elems, rhs.nRows, rhs.nCols);
	}

	Matrix Matrix::random(int nRows, int nCols, Range const & range) {
		Matrix res(nRows, nCols);

		for (int i = 0; i < nRows; ++i) {
			for (int j = 0; j < nCols; ++j) {
				res.setElem(
						i,
						j,
						util::Rand<Real>::getInstance().next(
								range.getMin(),
								range.getMax()
						)
				);
			}
		}

		return res;
	}

	Matrix Matrix::zero(int nRows, int nCols) {
		return Matrix(nRows, nCols);
	}
	
	bool Matrix::equals(Matrix const & rhs, Real eps) const {
		if (this == &rhs) {
			return true;
		}

		if (this->getNRows() != rhs.getNRows()) {
			return false;
		}

		if (this->getNCols() != rhs.getNCols()) {
			return false;
		}

		for (int i = 0; i < getNRows(); ++i) {
			for (int j = 0; j < getNCols(); ++j) {
				if (Math<Real>::abs(this->getElem(i, j) - rhs.getElem(i, j)) > eps) {
					return false;
				}
			}
		}

		return true;
	}

	Real Matrix::getElem(int i, int j) const {
		return this->elems[i][j];
	}

	int Matrix::getNRows() const {
		return nRows;
	}

	int Matrix::getNCols() const {
		return nCols;
	}

	void Matrix::setElem(int i, int j, Real val) {
		this->elems[i][j] = val;
	}

	Matrix Matrix::mult(Matrix const & rhs) const {
		//std::cout << "$$$$$Matrix mult(Matrix const & rhs) const\n";
		
		if (this->getNCols() == rhs.getNRows()) {
			Matrix res(this->getNRows(), rhs.getNCols());

			for (int i = 0; i < res.getNRows(); ++i) {
				for (int j = 0; j < res.getNCols(); ++j) {
					double val = 0.0;

					for (int k = 0; k < this->getNCols(); ++k) {
						val += this->getElem(i, k) * rhs.getElem(k, j);
					}

					res.setElem(i, j, val);
				}
			}

			return res;
		} else {
			throw IllegalArgumentException("this->getNCols() DOESN'T MATCH rhs.getNRows()");
		}
	}

	Vector Matrix::mult(Vector const & rhs) const {
		/*std::cout << "%%%%%Vector mult(Vector const & rhs) const\n";
		std::cout << "this->getNCols() = " << this->getNCols() << "\n";
		std::cout << "rhs.length() = " << rhs.length() << "\n";*/
		
		if (this->getNCols() == rhs.length()) {
			Vector res(this->getNRows());

			for (int i = 0; i < this->getNRows(); ++i) {
				double val = 0.0;

				for (int j = 0; j < rhs.length(); ++j) {
					val += this->getElem(i, j) * rhs.getElem(j);
				}

				res.setElem(i, val);
			}

			return res;
		} else {
			throw IllegalArgumentException("this->getNCols() DOESN'T MATCH rhs.length()");
		}
	}

	void Matrix::test() {
		Matrix m1(3, 3);
		m1.setElem(0, 0, 1);
		m1.setElem(0, 1, 4);
		m1.setElem(0, 2, -2);
		//m1.setElem(0, 3, -2);
		m1.setElem(1, 0, -7);
		m1.setElem(1, 1, 3);
		m1.setElem(1, 2, 5);
		//m1.setElem(1, 3, -2);
		m1.setElem(2, 0, 9);
		m1.setElem(2, 1, -6);
		m1.setElem(2, 2, -8);
		//m1.setElem(2, 3, -2);

		Matrix m2 = m1.mult(m1);
		Matrix m3(3, 3);
		m3.setElem(0, 0, -45);
		m3.setElem(0, 1, 28);
		m3.setElem(0, 2, 34);
		m3.setElem(1, 0, 17);
		m3.setElem(1, 1, -49);
		m3.setElem(1, 2, -11);
		m3.setElem(2, 0, -21);
		m3.setElem(2, 1, 66);
		m3.setElem(2, 2, 16);

		std::cout << "m2 =\n" << m2 << std::endl;;
		std::cout << "m1 * m1 == m3 ?" << m2.equals(m3, (Real)1.0e-6) << std::endl;

		Vector v1(3);
		v1.setElem(0, 31);
		v1.setElem(1, -59);
		v1.setElem(2, 67);

		Vector v2 = m1.mult(v1);
		Vector v3(3);
		v3.setElem(0, -339);
		v3.setElem(1, -59);
		v3.setElem(2, 97);
		std::cout << "v2 = " << v2 << std::endl;;
		std::cout << "v2.equals(v3) ? " << v2.equals(v3, (Real)1.0e-6) << std::endl;
		

		std::cout << "m1=\n" << m1 << std::endl;
		
		/*try {
			try (FileOutputStream fileOut = new FileOutputStream("/tmp/matrix.ser")) {
				ObjectOutputStream out = new ObjectOutputStream(fileOut);
				out.writeObject(m1);
				out.close();
			}
			System.out.printf("Serialized data is saved in /tmp/matrix.ser");
		} catch (IOException i) {
			System.err.println("SerializeDemo IOException");
			System.err.println("i.getClass() = " + i.getClass());
			System.err.println("i.getMessage() = " + i.getMessage());
		}
		
		Matrix m4 = null;
		
		try {
			try (FileInputStream fileIn = new FileInputStream("/tmp/matrix.ser")) {
				ObjectInputStream in = new ObjectInputStream(fileIn);
				m4 = (Matrix) in.readObject();
				in.close();
			}
		} catch (IOException i) {
			System.err.println("DeserializeDemo IOException");
			System.err.println("i.getMessage() = " + i.getMessage());
			return;
		} catch (ClassNotFoundException c) {
			System.err.println("Matrix class not found");
			return;
		}

		System.out.println("Deserialized Simulation...");
		System.out.println("simulation: \n" + m4);*/
	}

	std::ostream & operator<<(std::ostream & out, Matrix const & mat) {
		for (int i = 0; i < mat.getNRows(); ++i) {
			for (int j = 0; j < mat.getNCols(); ++j) {
				out << std::right << std::setw(16)
						<< std::setprecision(6) << mat.getElem(i, j);
			}

			out << "\n";
		}

		return out;
	}
}