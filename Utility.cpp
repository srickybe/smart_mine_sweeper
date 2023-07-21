#include "Utility.h"
#include <fstream>
#include <iostream>
#include <map>
#include "Math.h"
#include "Polygon.h"
#include "Triangle.h"
#include "Vector3D.h"

namespace ngn {

	Real Utility::areaOfTriangle(
		Triangle const & triangle, 
		std::vector<Vector3D> const & vertices
	) {
		Vector3D v1 = Vector3D::sub(vertices[triangle.getVertexIndex(1)], vertices[triangle.getVertexIndex(0)]);
		Vector3D v2 = Vector3D::sub(vertices[triangle.getVertexIndex(2)], vertices[triangle.getVertexIndex(0)]);
		Vector3D v3 = v1.cross(v2);
		Real len = v3.length();
		Real res = 0.5 * len;

				return res;		
	}
	
	std::pair<std::shared_ptr<std::vector<Triangle>>, std::shared_ptr<std::vector<Vector3D>>>
	Utility::divideTrianglesInFour(
		std::vector<Triangle> const & triples,
		std::vector<Vector3D> const & points
	) {
		std::shared_ptr<std::vector<Triangle>> triangles;
		triangles = std::make_shared<std::vector<Triangle>>();
		std::shared_ptr<std::vector<Vector3D>> vertices; 
		vertices = std::make_shared<std::vector<Vector3D>>(points);
		//std::cout << "area[0] = " << areaOfTriangle(triples[0], points) << "\n";

		typedef std::pair<int unsigned, int unsigned> PairOfVertexIndices;
		typedef std::pair<PairOfVertexIndices, int unsigned> PairOfPairOfVertexIndicesAndMidpointIndex;
		typedef std::map<PairOfVertexIndices, int unsigned> IndicesOfMidPointsOfPairOfVertices;
		IndicesOfMidPointsOfPairOfVertices indices;

		for (int unsigned i = 0; i < triples.size(); ++i) {
			//std::cout << "i = " << i << endl;
			Triangle triangle = triples[i];
			int unsigned a = triangle.getVertexIndex(0);
			int unsigned b = triangle.getVertexIndex(1);
			int unsigned c = triangle.getVertexIndex(2);
			std::vector<PairOfVertexIndices> pairsOfVertexIndices;
			pairsOfVertexIndices.push_back(
				a < b ? 
				PairOfVertexIndices(a, b): 
				PairOfVertexIndices(b, a)
			);
			pairsOfVertexIndices.push_back(
				b < c ? 
				PairOfVertexIndices(b, c): 
				PairOfVertexIndices(c, b)
			);
			pairsOfVertexIndices.push_back(
				a < c ? 
				PairOfVertexIndices(a, c): 
				PairOfVertexIndices(c, a)
			);

			std::vector<typename IndicesOfMidPointsOfPairOfVertices::iterator> iterators;

			//std::cout << "OK1\n";
			for (int unsigned j = 0; j < pairsOfVertexIndices.size(); ++j) {
				typename IndicesOfMidPointsOfPairOfVertices::iterator iter;
				iter = indices.find(pairsOfVertexIndices[j]);
				iterators.push_back(iter);
				//std::cout << "iter == indices.end() ? " << (iter == indices.end() ? "true": "false") << "\n";
			}

			std::vector<std::pair<typename IndicesOfMidPointsOfPairOfVertices::iterator, bool>> insertionResults;

			for (int unsigned j = 0; j < iterators.size(); ++j) {
				insertionResults.push_back(std::pair<typename IndicesOfMidPointsOfPairOfVertices::iterator, bool>());
			}

			//std::cout << "OK2\n";
			for (int unsigned j = 0; j < pairsOfVertexIndices.size(); ++j) {
				if (iterators[j] == indices.end()) {
					//std::cout << "iterators[" << j << "] == indices.end()\n";
					Vector3D vec = vertices->operator [](pairsOfVertexIndices[j].first);
					vec.add(vertices->operator [](pairsOfVertexIndices[j].second));
					vec.mult(0.5);
					vertices->push_back(vec);
					int unsigned indexOfNewVector3D = vertices->size() - 1;
					insertionResults[j] = 
						indices.insert(
							PairOfPairOfVertexIndicesAndMidpointIndex(
								pairsOfVertexIndices[j], 
								indexOfNewVector3D
							)
						);
					//std::cout << "the middle point of vertex[" << pairsOfVertexIndices[j].first << "] and ";
					//std::cout << "vertex[" << pairsOfVertexIndices[j].second << "] is vertex[" << indexOfNewVector3D << "]\n";
					iterators[j] = insertionResults[j].first;
				}
			}

			//std::cout << "OK3\n";
			
			int unsigned Mab = iterators[0]->second;
			int unsigned Mbc = iterators[1]->second;
			int unsigned Mac = iterators[2]->second;

			//std::cout << "OK4\n";
			triangles->push_back(Triangle(a, Mab, Mac));
			triangles->push_back(Triangle(Mab, b, Mbc));
			triangles->push_back(Triangle(Mbc, c, Mac));
			triangles->push_back(Triangle(Mab, Mbc, Mac));
		}

		//std::cout << "***************vertices.size() = " << vertices->size() << "\n";
		//std::cout << "***************triangles.size() = " << triangles->size() << "\n";

		//for (int unsigned i = 0; i < triangles->size(); ++i) {
		//	std::cout << "triangles[" << i << "] = " << triangles->operator[](i) << "\n";
		//	std::cout << "area[" << i << "] = ";
		//	std::cout << areaOfTriangle((*triangles)[i], (*vertices)) << "\n";
		//}

		//std::cout << "############################################################\n";
		
		return std::make_pair(triangles, vertices);
	}

    template< typename T >
    void Utility::print_vector(const std::vector< T > & vec) {
        int unsigned n_items = vec.size();

        for (int unsigned i = 0; i < n_items; ++i) {
            std::cout << vec[i] << "\n";
        }
    }

    bool const Utility::is_number(char ch) {
        return ( ch >= '0' && ch <= '9');
    }

    
    void Utility::read_float(char* buffer, int buf_size, int& pos, Real & res) {
        int ipos = pos;
        long double exp = 0;
        int epos = -1;

        long double num = read_number(buffer, buf_size, pos);

        if (buffer[pos] != '\0' && pos < buf_size) {
            if (buffer[pos] == '.') {
                epos = pos;
                ++pos;
                long double dec = read_number(buffer, buf_size, pos);
                dec *= Math<long>::pow(10.L, epos + 1 - pos);

                if (buffer[ipos] == '-') {
                    num -= dec;
                } else {
                    num += dec;
                }
            }

            if (buffer[pos] == 'e') {
                ++pos;
                exp = read_number(buffer, buf_size, pos);
            }
        }

        if (exp != 0) {
            num *= Math<long>::pow(10.L, exp);
        }

        res = static_cast<Real> (num);
    }

    long double Utility::read_number(char* buffer, int buf_size, int& pos) {
        bool negative = false;

        if (buffer[pos] == '-') {
            negative = true;
            ++pos;
        }

        long double num = buffer[pos] - '0';
        ++pos;

        while ((buffer[pos] != '\0') &&
                (buffer[pos] >= '0') &&
                (buffer[pos] <= '9') &&
                (pos < buf_size)) {
            num *= 10;
            num += buffer[pos] - '0';
            ++pos;
        }

        if (negative) {
            num *= -1;
        }

        return num;
    }

    
    void Utility::shift(Real & first, Real & second, Real & third, Real & fourth) {
        first = second;
        second = third;
        third = fourth;
    }

    
    Real Utility::sign(Real a, Real b) {
        double result;

        if (b > 0.0) {
            result = std::abs(a);
        } else {
            result = -std::abs(a);
        }

        return result;
    }

    void Utility::read_vector(std::ifstream & in, std::vector<Polygon>& nuples) {
        assert(in);

        int n_nuples;
        in.read(reinterpret_cast<char*> (&n_nuples), sizeof ( int));

        int max_indices = 64;
        std::vector< int unsigned > indices(max_indices);

        for (int i = 0; i < n_nuples; ++i) {
            int n_indices;
            in.read(reinterpret_cast<char*> (&n_indices), sizeof ( int));
            assert(n_indices > 4);

            if (n_indices > max_indices) {
                max_indices = n_indices;
                indices.resize(max_indices);
            }

            for (int i = 0; i < n_indices; ++i) {
                in.read(reinterpret_cast<char*> (&indices[ i ]), sizeof ( int));
            }

            nuples.push_back(Polygon(&indices[0], n_indices));
        }
    }

    void Utility::write_vector(std::ofstream & out, std::vector<Polygon> const & nuples) {
        assert(out);

        int n_nuples = nuples.size();
        out.write(reinterpret_cast<char const *> (&n_nuples), sizeof ( int));

        for (int i = 0; i < n_nuples; ++i) {
            for (int unsigned j = 0; j < nuples[i].getNumberOfVertexIndices(); ++j) {
                out.write(reinterpret_cast<char const *> (&nuples[i].getVertexIndex(j)), sizeof ( int unsigned ));
            }
        }
    }

    void Utility::read_string(std::ifstream & in, std::string& str) {
        //std::cout << "void read_string( std::ifstream & in, std::string& str )\n";
        assert(in);

        str.clear();
        int unsigned n_chars;
        in.read(reinterpret_cast<char*> (&n_chars), sizeof ( int unsigned));
        //std::cout << "n_chars = " << n_chars << "\n";

        if (n_chars) {
            str.resize(n_chars);

            for (int unsigned i = 0; i < n_chars; ++i) {
                in.read(reinterpret_cast<char*> (&str[i]), sizeof ( char));
                //std::cout << "str[" << i << "] = " << str[i] << "\n";
            }
        }
    }

    void Utility::write_string(std::ofstream & out, std::string const & str) {
        //std::cout << "void write_string( std::ofstream & out, std::string const & str )\n";
        assert(out);

        int unsigned n_chars = str.size();
        //std::cout << "n_chars = " << n_chars << "\n";
        out.write(reinterpret_cast<char const *> (&n_chars), sizeof ( int unsigned));

        for (int unsigned i = 0; i < n_chars; ++i) {
            out.write(reinterpret_cast<char const *> (&str[i]), sizeof ( char));
            //std::cout << "str[" << i << "] = " << str[i] << "\n";
        }
    }

    template< typename T >
    void Utility::read_vector(std::ifstream & in, std::vector< T > & vec) {
        assert(in);

        int unsigned n_elems;
        in.read(reinterpret_cast<char*> (&n_elems), sizeof ( int unsigned));

        vec.resize(n_elems);

        for (int unsigned i = 0; i < n_elems; ++i) {
            in.read(reinterpret_cast<char*> (&vec[ i ]), sizeof ( T));
        }
    }

    template< typename T >
    void Utility::write_vector(std::ofstream & out, const std::vector< T > & vec) {
        assert(out);

        int unsigned n_elems = vec.size();
        out.write(reinterpret_cast<char const *> (&n_elems), sizeof ( int unsigned));

        typename std::vector< T >::const_iterator it = vec.begin(),
                end = vec.end();
        for (; it != end; ++it) {
            out.write(reinterpret_cast<char const *> (&*it), sizeof ( T));
        }
    }
}