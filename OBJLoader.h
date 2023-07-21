#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <boost/shared_array.hpp>
#include <cassert>
#include <fstream>
#include <map>
#include <memory>
#include <vector>
#include "Mesh.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "VTN.h"

namespace ngn {
	
    class OBJLoader;
    class MaterialManager;
    class Model;
    std::map<std::string, void(*)(OBJLoader &) > build_map();
    void read_face(OBJLoader &);
    void read_material_name(OBJLoader &);
    void read_materials(OBJLoader &);
    void read_mesh_name(OBJLoader &);
    void read_normal(OBJLoader &);
    void read_point(OBJLoader &);
    void read_2d_texture_coordinates(OBJLoader &);
    void read_3d_texture_coordinates(OBJLoader &);
    void read_vertex(OBJLoader &, int &);


    class OBJLoader {
        
        friend void read_face(OBJLoader &);
        friend void read_material_name(OBJLoader &);
        friend void read_materials(OBJLoader &);
        friend void read_mesh_name(OBJLoader &);
        friend void read_normal(OBJLoader &);
        friend void read_point(OBJLoader &);
        friend void read_2d_texture_coordinates(OBJLoader &);
        friend void read_3d_texture_coordinates(OBJLoader &);
        friend void read_vertex(OBJLoader &, int &);

    public:
        OBJLoader(int buffer_size, int string_size);
        void loadOBJ(char const *, MaterialManager &, Model &);

    private:
        boost::shared_array<char> buffer_;
        int buffer_size_;
        boost::shared_array<char> string_;
        int string_size_;

        std::vector<Vector3D> points_;
        std::shared_ptr<std::vector<Vector2D>> texture_coords_2_;
        std::shared_ptr<std::vector<Vector3D>> texture_coords_3_;
        std::vector<Vector3D> normals_;

        std::shared_ptr<std::vector<Vector3D>> shared_points_;
        std::shared_ptr<std::vector<Vector2D>> shared_textures_2_;
        std::shared_ptr<std::vector<Vector3D>> shared_textures_3_;
        std::shared_ptr<std::vector<Vector3D>> shared_normals_;

        std::string file_;
        Model * model_;
        MaterialManager * material_manager_;
        std::map<VTN, int> vtns_;

        std::shared_ptr<Mesh> current_mesh_;
        VTN current_vtn_;
        bool normal_in_file_;
        bool texture_coordinates_in_file_;

        static std::map<std::string, void(*)(OBJLoader &) > functions_;
        void clear(char *, int);
    };

    ////////////////////////////////////////////////////////////////////////
}

#endif // OBJ_LOADER_H
