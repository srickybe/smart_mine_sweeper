#include "Material.h"
#include <iostream>

namespace ngn {

    Material::Material()
    : name_(),
    color_properties_(),
    texture_properties_() {
    }

    std::string const & Material::getName()const {
        return name_;
    }

    void Material::setName(std::string const & name) {
        name_ = name;
    }

    RGBColor const & Material::get_Ka()const {
        return color_properties_.Ka;
    }

    std::string const & Material::get_map_Ka_filename()const {
        return texture_properties_.Ka_filename;
    }

    RGBColor const & Material::get_Kd()const {
        return color_properties_.Kd;
    }

    std::string const & Material::get_map_Kd_filename()const {
        return texture_properties_.Kd_filename;
    }

    RGBColor const & Material::get_Ks()const {
        return color_properties_.Ks;
    }

    std::string const & Material::get_map_Ks_filename()const {
        return texture_properties_.Ks_filename;
    }

    RGBColor const & Material::get_Tf()const {
        return color_properties_.Tf;
    }

    int const Material::get_illum()const {
        return color_properties_.illum;
    }

    float const Material::get_d()const {
        return color_properties_.d;
    }

    std::string const & Material::get_map_d_filename()const {
        return texture_properties_.d_filename;
    }

    float const Material::get_Ns()const {
        return color_properties_.Ns;
    }

    std::string const & Material::get_map_Ns_filename()const {
        return texture_properties_.Ns_filename;
    }

    float const Material::get_sharpness()const {
        return color_properties_.sharpness;
    }

    float const Material::get_Ni()const {
        return color_properties_.Ni;
    }

    void Material::set_Ka(RGBColor const & Ka) {
        color_properties_.Ka = Ka;
    }

    void Material::set_map_Ka_filename(std::string const & Ka_filename) {
        texture_properties_.Ka_filename = Ka_filename;
    }

    void Material::set_Kd(RGBColor const & Kd) {
        color_properties_.Kd = Kd;
    }

    void Material::set_map_Kd_filename(std::string const & Kd_filename) {
        texture_properties_.Kd_filename = Kd_filename;
    }

    void Material::set_Ks(RGBColor const & Ks) {
        color_properties_.Ks = Ks;
    }

    void Material::set_map_Ks_filename(std::string const & Ks_filename) {
        texture_properties_.Ks_filename = Ks_filename;
    }

    void Material::set_Tf(RGBColor const & Tf) {
        color_properties_.Tf = Tf;
    }

    void Material::set_illum(int illum) {
        color_properties_.illum = illum;
    }

    void Material::set_d(float d) {
        color_properties_.d = d;
    }

    void Material::set_map_d_filename(std::string const & d_filename) {
        texture_properties_.d_filename = d_filename;
    }

    void Material::set_Ns(float Ns) {
        color_properties_.Ns = Ns;
    }

    void Material::set_map_Ns_filename(std::string const & Ns_filename) {
        texture_properties_.Ns_filename = Ns_filename;
    }

    void Material::set_sharpness(float sharpness) {
        color_properties_.sharpness = sharpness;
    }

    void Material::set_Ni(float Ni) {
        color_properties_.Ni = Ni;
    }

    void Material::info(std::ostream & out)const {
        out << "name: " << name_;
        out << "\nambient reflectivity = " << color_properties_.Ka;
        out << "\ndiffusive reflectivity = " << color_properties_.Kd;
        out << "\nspecular reflectivity = " << color_properties_.Ks;
        out << "\ntransmission filter = " << color_properties_.Tf;
        out << "\nillumination model = " << color_properties_.illum;
        out << "\ndissolve = " << color_properties_.d;
        out << "\nspecular exponent = " << color_properties_.Ns;
        out << "\nsharpness = " << color_properties_.sharpness;
        out << "\noptical density = " << color_properties_.Ni << "\n";

        if (!texture_properties_.Ka_filename.empty()) {
            out << "map_Ka filename: " << texture_properties_.Ka_filename << "\n";
        }

        if (!texture_properties_.Kd_filename.empty()) {
            out << "map_Kd filename: " << texture_properties_.Kd_filename << "\n";
        }

        if (!texture_properties_.Ks_filename.empty()) {
            out << "map_Ks filename: " << texture_properties_.Ks_filename << "\n";
        }

        out << "\n";
    }
}