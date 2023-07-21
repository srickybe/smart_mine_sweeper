#ifndef MATERIAL_H
#define MATERIAL_H

#include <iosfwd>
#include <string>
#include "RGBColor.h"

namespace ngn {

    class Material {
    public:
        Material();
        std::string const & getName()const;
        void setName(std::string const &);

        RGBColor const & get_Ka()const;
        std::string const & get_map_Ka_filename()const;
        RGBColor const & get_Kd()const;
        std::string const & get_map_Kd_filename()const;
        RGBColor const & get_Ks()const;
        std::string const & get_map_Ks_filename()const;
        RGBColor const & get_Tf()const;
        int const get_illum()const;
        float const get_d()const;
        std::string const & get_map_d_filename()const;
        float const get_Ns()const;
        std::string const & get_map_Ns_filename()const;
        float const get_sharpness()const;
        float const get_Ni()const;

        void set_Ka(RGBColor const &);
        void set_map_Ka_filename(std::string const &);
        void set_Kd(RGBColor const &);
        void set_map_Kd_filename(std::string const &);
        void set_Ks(RGBColor const &);
        void set_map_Ks_filename(std::string const &);
        void set_Tf(RGBColor const &);
        void set_illum(int);
        void set_d(float);
        void set_map_d_filename(std::string const &);
        void set_Ns(float);
        void set_map_Ns_filename(std::string const &);
        void set_sharpness(float);
        void set_Ni(float);

        void info(std::ostream &)const;

    private:

        class Color_properties {
        public:
            RGBColor Ka;
            RGBColor Kd;
            RGBColor Ks;
            RGBColor Tf;
            int illum;
            float d;
            float Ns;
            float sharpness;
            float Ni;

            Color_properties()
            : Ka(0.2f, 0.2f, 0.2f),
            Kd(0.8f, 0.8f, 0.8f),
            Ks(0.0f, 0.0f, 0.0f),
            Tf(0.0f, 0.0f, 0.0f),
            illum(1),
            d(1.0f),
            Ns(0.0f),
            sharpness(60.0f),
            Ni(1.0f) {
            }
        };

        class Texture_properties {
        public:
            std::string Ka_filename;
            std::string Kd_filename;
            std::string Ks_filename;
            std::string Ns_filename;
            std::string d_filename;

            Texture_properties()
            : Ka_filename(),
            Kd_filename(),
            Ks_filename(),
            Ns_filename(),
            d_filename() {

            }
        };

        std::string name_;
        Color_properties color_properties_;
        Texture_properties texture_properties_;
    };
}

#endif // MATERIAL_H