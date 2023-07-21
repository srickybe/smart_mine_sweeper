#include "OBJLoader.h"
#include "Face.h"
#include "Line.h"
#include "MTLLoader.h"
#include "MaterialManager.h"
#include "Model.h"
#include "Polygon.h"
#include "Quad.h"
#include "Triangle.h"
#include "Utility.h"

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>

namespace ngn {
   
    std::map<std::string, void(*)(OBJLoader &) > OBJLoader::functions_ = build_map();

    std::map<std::string, void(*)(OBJLoader &) > build_map() {
        std::map < std::string, void(*)(OBJLoader &) > functions;

        functions.insert(
                std::pair< char const *, void(*)(OBJLoader &) >(
                "f ",
                read_face
                )
                );

        functions.insert(
                std::pair< char const *, void(*)(OBJLoader &) >(
                "g ",
                read_mesh_name
                )
                );

        functions.insert(
                std::pair< char const *, void(*)(OBJLoader &) >(
                "mt",
                read_materials
                )
                );

        functions.insert(
                std::pair< char const *, void(*)(OBJLoader &) >(
                "us",
                read_material_name
                )
                );

        functions.insert(
                std::pair< char const *, void(*)(OBJLoader &) >(
                "v ",
                read_point
                )
                );

        functions.insert(
                std::pair< char const *, void(*)(OBJLoader &) >(
                "vn",
                read_normal
                )
                );

        return functions;
    }

    
    OBJLoader::OBJLoader(
            int buffer_size,
            int string_size
            )
    : buffer_(new char[ buffer_size ]),
    buffer_size_(buffer_size),
    string_(new char[ string_size ]),
    string_size_(string_size),
    points_(),
    texture_coords_2_(new std::vector<Vector2D>()),
    texture_coords_3_(new std::vector<Vector3D>()),
    normals_(),
    shared_points_(new std::vector<Vector3D>()),
    shared_textures_2_(new std::vector<Vector2D>()),
    shared_textures_3_(new std::vector<Vector3D>()),
    shared_normals_(new std::vector<Vector3D>()),
    file_(),
    model_(),
    material_manager_(),
    vtns_(),
    current_mesh_(),
    current_vtn_(),
    normal_in_file_(false),
    texture_coordinates_in_file_(false) {
        assert(buffer_size > 128);
        assert(string_size > 64);
    }

    void OBJLoader::loadOBJ(
            char const * file,
            MaterialManager & material_manager,
            Model & model
            ) {
        file_.assign(file);
        std::cout << "file = " << file_ << "\n";
        std::ifstream in(file_.c_str());
        assert(in);

        OBJLoader::functions_.insert(
                std::pair< char const *, void(*)(OBJLoader &) >(
                "vt",
                read_3d_texture_coordinates
                )
                );

        model_ = &model;
        model_->setPoints(shared_points_);
        material_manager_ = &material_manager;
        //current_mesh_ = std::shared_ptr<Mesh>(new Mesh()); 
        std::string str("  ");

        while (in.getline(&buffer_[0], buffer_size_, '\n')) {
            /*for (int i = 0; i < buffer_size_; ++i) {
                std::cout << buffer_[i];
            }
            
            std::cout << std::endl;*/
            
            str[0] = buffer_[0];
            str[1] = buffer_[1];

            typename std::map < std::string, void(*)(OBJLoader &) >::iterator res =
                    functions_.find(str.c_str());

            if (res != functions_.end()) {
                res->second(*this);
            } else {
                //std::cout << "str = " << str << "\n";
            }

            this->clear(buffer_.get(), buffer_size_);
            this->clear(string_.get(), string_size_);
        }

        int n_vtns = vtns_.size();
        //std::cout << "vtns_.size() = " << n_vtns << "\n";

        typedef std::map<VTN, int> map_type;
        typedef map_type::const_iterator const_iterator;

        if (texture_coordinates_in_file_) {
            if (normal_in_file_) {
                shared_points_->resize(n_vtns);
                shared_normals_->resize(n_vtns);
                shared_textures_3_->resize(n_vtns);

                for (const_iterator it = vtns_.begin(); it != vtns_.end(); ++it) {
                    int j = it->second;
                    (*shared_points_)[j] = points_[it->first.point_index];

                    int k = it->first.texture_index;

                    if (k > -1) {
                        (*shared_textures_3_)[j] = (*texture_coords_3_)[k];
                    } else {
                        (*shared_textures_3_)[j] = Vector3D::zero();
                    }

                    int l = it->first.normal_index;

                    if (l > -1) {
                        (*shared_normals_)[j] = normals_[l];
                    } else {
                        (*shared_normals_)[j] = Vector3D::zero();
                    }
                }
            } else {
                shared_points_->resize(n_vtns);
                shared_textures_3_->resize(n_vtns);

                for (
                        const_iterator it = vtns_.begin();
                        it != vtns_.end();
                        ++it
                        ) {
                    int j = it->second;
                    (*shared_points_)[j] = points_[it->first.point_index];

                    int k = it->first.texture_index;

                    if (k > -1) {
                        (*shared_textures_3_)[j] = (*texture_coords_3_)[k];
                    } else {
                        (*shared_textures_3_)[j] = Vector3D::zero();
                    }
                }
            }
        } else {
            if (normal_in_file_) {
                shared_points_->resize(n_vtns);
                shared_normals_->resize(n_vtns);

                for (
                        const_iterator it = vtns_.begin();
                        it != vtns_.end();
                        ++it
                        ) {
                    int j = it->second;
                    (*shared_points_)[j] = points_[it->first.point_index];

                    int l = it->first.normal_index;

                    if (l > -1) {
                        (*shared_normals_)[j] = normals_[l];
                    } else {
                        (*shared_normals_)[j] = Vector3D::zero();
                    }
                }
            } else {
                shared_points_->resize(n_vtns);

                for (
                        const_iterator it = vtns_.begin();
                        it != vtns_.end();
                        ++it
                        ) {
                    int j = it->second;
                    (*shared_points_)[j] = points_[it->first.point_index];
                }
            }
        }

        for (
                typename Model::iterator it = model_->begin();
                it != model_->end();
                ++it
                ) {
            (*it)->setPoints(shared_points_);
            (*it)->setTextureCoordinates(shared_textures_2_);
            (*it)->setTextureCoordinates(shared_textures_3_);
            (*it)->setNormals(shared_normals_);

            if ((**it).replaceDegeneratedPrimitives((Real) 1.0e-6)) {
                std::cout << "mesh " << (**it).getName();
                std::cout << " had invalid triples!\n";
            }
        }
        
        //model_->setGeometryFromMeshes();
    }

    void OBJLoader::clear(char * buffer, int buffer_size) {
        for (int i = 0; i < buffer_size; ++i) {
            buffer[i] = '\0';
        }
    }

    void read_mesh_name(OBJLoader & objLoader) {
        int i = 2;

        for (; i < objLoader.string_size_ && objLoader.buffer_[i] != '\0'; ++i) {
            objLoader.string_[i - 2] = objLoader.buffer_[i];
        }

        if (objLoader.buffer_[i] == '\0') {
            objLoader.string_[i] = '\0';
        }

        std::string name(objLoader.string_.get());
        //std::cout << "mesh name = " << name << "\n";
        objLoader.current_mesh_ = objLoader.model_->createMesh(name);
    }

    void read_material_name(OBJLoader & objLoader) {
        int i = 7;

        for (; i < objLoader.string_size_ && objLoader.buffer_[i] != '\0'; ++i) {
            objLoader.string_[i - 7] = objLoader.buffer_[i];
        }

        if (objLoader.buffer_[i] == '\0') {
            objLoader.string_[i] = '\0';
        }

        std::string name(objLoader.string_.get());
        //std::cout << "material name = " << name << "\n";

        assert(objLoader.current_mesh_ != 0);

        objLoader.current_mesh_->setMaterial(
                objLoader.material_manager_->getMaterial(name)
                );
    }

    void read_materials(OBJLoader & objLoader) {
        int i = 7;

        for (; i < objLoader.string_size_ && objLoader.buffer_[i] != '\0'; ++i) {
            objLoader.string_[i - 7] = objLoader.buffer_[i];
        }

        if (objLoader.buffer_[i] == '\0') {
            objLoader.string_[i] = '\0';
        }

        //Extraction of the parent directory from the path of the file
        std::string str(objLoader.file_.c_str());
        char const * it = &objLoader.file_[0];

        while (*it != '\0' && *it != '/' && *it != '\\') {
            ++it;
        }

        if (*it != '\0') {
            char const * it1 = it;
            ++it;

            while (*it != '\0') {
                if (*it == '\\' || *it == '/') {
                    it1 = it;
                }

                ++it;
            }

            std::string lib_file(objLoader.file_.c_str(), it1);
            lib_file += *it1;
            lib_file += std::string(objLoader.string_.get());

            //std::cout << "material library file = " << lib_file << "\n";

            MTLLoader mtlLoader;
            mtlLoader.loadMTL(lib_file.c_str(), *objLoader.material_manager_);
        } else {
            std::string filename(objLoader.string_.get());
            //std::cout << "material library file = " << filename  << "\n";

            MTLLoader mtlLoader;
            mtlLoader.loadMTL(filename.c_str(), *objLoader.material_manager_);
        }
    }

    void read_normal(OBJLoader & objLoader) {
        Vector3D normal;
        int cur_pos = 3;

        for (int i = 0; i < 3; ++i) {
            Real tmp;

            Utility::read_float(
                    &objLoader.buffer_[0],
                    objLoader.buffer_size_,
                    cur_pos,
                    tmp
                    );
            normal.set(i, tmp);
            ++cur_pos;
        }

        objLoader.normals_.push_back(normal);

        //std::cout << "normal = " << normal << "\n";
    }

    void read_3d_texture_coordinates(OBJLoader & objLoader) {
        Vector3D texture_coordinates;
        int cur_pos = 3;

        for (int i = 0; i < 2; ++i) {
            Real tmp;

            Utility::read_float(
                    &objLoader.buffer_[0],
                    objLoader.buffer_size_,
                    cur_pos,
                    tmp
                    );
            texture_coordinates.set(i, tmp);
            ++cur_pos;
        }

        if (Utility::is_number(objLoader.buffer_[ cur_pos ])) {
            Real tmp;

            Utility::read_float(
                    &objLoader.buffer_[0],
                    objLoader.buffer_size_,
                    cur_pos,
                    tmp
                    );
            texture_coordinates.setZ(tmp);
        } else {
            texture_coordinates.setZ((Real) 0.0);
        }

        objLoader.texture_coords_3_->push_back(texture_coordinates);

        //std::cout << "texture_coords = " << texture_coordinates << "\n";
    }

    void read_point(OBJLoader & objLoader) {
        Vector3D point;
        int cur_pos = 2;

        for (int i = 0; i < 3; ++i) {
            Real tmp;

            Utility::read_float(
                    &objLoader.buffer_[0],
                    objLoader.buffer_size_,
                    cur_pos,
                    tmp
                    );
            point.set(i, tmp);
            ++cur_pos;
        }

        objLoader.points_.push_back(point);

        //std::cout << "point = " << point << "\n";
    }

    void read_vertex(
            OBJLoader & objLoader,
            int & pos
            ) {
        if (!Utility::is_number(objLoader.buffer_[pos])) {
            std::cout << "buffer_ =\n" << objLoader.buffer_.get() << "\n";
            std::cout << "pos = " << pos << "\n";

            assert(false);
        }

        objLoader.current_vtn_.point_index = static_cast<int> (
                Utility::read_number(
                &objLoader.buffer_[0],
                objLoader.buffer_size_,
                pos)
                );

        assert(objLoader.current_vtn_.point_index > 0);

        --objLoader.current_vtn_.point_index;
        objLoader.current_vtn_.texture_index = -1;
        objLoader.current_vtn_.normal_index = -1;

        if (objLoader.buffer_[pos] == '/') {
            ++pos;

            if (Utility::is_number(objLoader.buffer_[pos])) {
                objLoader.current_vtn_.texture_index = static_cast<int> (
                        Utility::read_number(
                        &objLoader.buffer_[0],
                        objLoader.buffer_size_,
                        pos
                        )
                        );

                assert(objLoader.current_vtn_.texture_index > 0);

                if (!objLoader.texture_coordinates_in_file_) {
                    objLoader.texture_coordinates_in_file_ = true;
                }

                --objLoader.current_vtn_.texture_index;

                if (objLoader.buffer_[pos] == '/') {
                    ++pos;

                    assert(Utility::is_number(objLoader.buffer_[pos]));

                    objLoader.current_vtn_.normal_index = static_cast<int> (
                            Utility::read_number(
                            &objLoader.buffer_[0],
                            objLoader.buffer_size_,
                            pos
                            )
                            );

                    assert(objLoader.current_vtn_.normal_index > 0);

                    if (!objLoader.normal_in_file_) {
                        objLoader.normal_in_file_ = true;
                    }

                    --objLoader.current_vtn_.normal_index;
                }
            } else {
                if (objLoader.buffer_[pos] == '/') {
                    ++pos;

                    assert(Utility::is_number(objLoader.buffer_[pos]));

                    objLoader.current_vtn_.normal_index = static_cast<int> (
                            Utility::read_number(
                            &objLoader.buffer_[0],
                            objLoader.buffer_size_,
                            pos
                            )
                            );

                    assert(objLoader.current_vtn_.normal_index > 0);

                    if (!objLoader.normal_in_file_) {
                        objLoader.normal_in_file_ = true;
                    }

                    --objLoader.current_vtn_.normal_index;
                } else {
                    assert(
                            Utility::is_number(objLoader.buffer_[pos]) ||
                            objLoader.buffer_[pos] == '/'
                            );
                }
            }
        } else {
            assert(
                    objLoader.buffer_[pos] == ' ' ||
                    objLoader.buffer_[pos] == '\0'
                    );
        }

        //std::cout << "current_vtn_ = " << load_obj.current_vtn_ << "\n";
    }

    void read_face(OBJLoader & objLoader) {
        assert(Utility::is_number(objLoader.buffer_[2]));
        int pos = 2;

        read_vertex(objLoader, pos);
        std::pair < std::map<VTN, int>::iterator, bool > res =
                objLoader.vtns_.insert(
                std::pair< VTN, int>(
                objLoader.current_vtn_,
                objLoader.vtns_.size()
                )
                );

        Face current_face;
        current_face.addIndex(res.first->second);

        while (true) {
            if (objLoader.buffer_[pos] != '\0' && pos < objLoader.buffer_size_) {
                if (objLoader.buffer_[pos] == ' ') {
                    while(objLoader.buffer_[pos] == ' ' && objLoader.buffer_[pos] != '\0') {
                        ++pos;
                    }

                    if (objLoader.buffer_[pos] == '\n' || (int) (objLoader.buffer_[pos]) == 13) {
                        break;
                    }

                    if (objLoader.buffer_[pos] != '\0') {
                        read_vertex(objLoader, pos);
                        std::pair < std::map<VTN, int>::iterator, bool > res =
                                objLoader.vtns_.insert(
                                std::pair< VTN, int>(
                                objLoader.current_vtn_,
                                objLoader.vtns_.size()
                                )
                                );
                        current_face.addIndex(res.first->second);
                    }
                } else {
                    assert((int) objLoader.buffer_[pos] == 13);
                    break;
                }
            } else {
                break;
            }
        }

        if (objLoader.current_mesh_ == 0) {
            objLoader.current_mesh_ = objLoader.model_->createMesh("");
        }
        
        switch (current_face.getNumberOfIndices()) {
            case 3:
                objLoader.current_mesh_->addTriangle(
                        Triangle(
                        current_face.getIndices()[0],
                        current_face.getIndices()[1],
                        current_face.getIndices()[2]
                        )
                        );
                break;

            case 4:
                objLoader.current_mesh_->addQuad(
                        Quad(
                        current_face.getIndices()[0],
                        current_face.getIndices()[1],
                        current_face.getIndices()[2],
                        current_face.getIndices()[3]
                        )
                        );
                break;

            case 2:
                objLoader.current_mesh_->addLine(
                        Line(
                        current_face.getIndices()[0],
                        current_face.getIndices()[1]
                        )
                        );
                break;

            default:
                assert(current_face.getNumberOfIndices() > 1);
                assert(current_face.getNumberOfIndices() < 10);

                objLoader.current_mesh_->addPolygon(
                        Polygon(
                        current_face.getIndices(),
                        current_face.getNumberOfIndices()
                        )
                        );

                break;
        }

        //std::cout << "current_face = " << current_face << "\n";
    }
}

	