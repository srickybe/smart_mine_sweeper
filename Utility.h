#ifndef UTILITY_H
#define UTILITY_H

#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "Real.h"

namespace ngn {
	
	class Polygon;
	class Triangle;
	class Vector3D;
	
	class Utility {
	public:
		static 
		std::pair<std::shared_ptr<std::vector<Triangle>>, std::shared_ptr<std::vector<Vector3D>>>
		divideTrianglesInFour(
			std::vector<Triangle> const & triangles,
			std::vector<Vector3D> const & vertices
		);
		
		static 
		Real 
		areaOfTriangle(
			Triangle const & triangle, 
			std::vector<Vector3D> const & vertices
		);
		
		static bool const is_number(char ch);
		 
		template<typename T>
		static void print_vector(const std::vector< T > & vec);
		
		static void read_float(char*, int, int&, Real &);
		static long double read_number(char*, int, int&);
		static void shift(Real &, Real &, Real &, Real &);
		static Real sign(Real, Real);
		static void read_vector(std::ifstream &, std::vector<Polygon>&);
		
		template< typename T >
		static void read_vector(std::ifstream & in, std::vector< T > & vec);
		
		static void write_vector(std::ofstream & out, std::vector<Polygon> const &);
		
		template< typename T >
		static void write_vector(std::ofstream & out, const std::vector< T > & vec);
	
		static void read_string(std::ifstream & in, std::string& str);
		static void write_string(std::ofstream & out, std::string const & str);
	};
	
}

#endif // UTILITY_H