#include "MTLLoader.h"
#include "MaterialManager.h"
#include "Real.h"
#include "Utility.h"
#include <boost/scoped_array.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>


namespace ngn {
	
    MTLLoader::MTLLoader() {
    }

    void MTLLoader::loadMTL(char const * filename, MaterialManager & manager)const {
        std::ifstream in(filename, std::ios::in);

        if (in) {
            boost::scoped_array<char> buffer(new char[100]);
            std::shared_ptr<Material> current_material;
            std::string material_name;
            int count = 0;
            int pos;
            char* c;
            Real reals[3];

            while (in.getline(buffer.get(), 100)) {
                switch (buffer[0]) {
                    case 'K':
                        pos = 3;

                        for (int unsigned i = 0; i < 3; ++i) {
                            Utility::read_float(buffer.get(), 100, pos, reals[i]);
                            ++pos;
                        }

                        switch (buffer[1]) {
                            case 'a':
                                current_material->set_Ka(
                                        RGBColor(reals[0], reals[1], reals[2]));
                                break;

                            case 'd':
                                current_material->set_Kd(
                                        RGBColor(reals[0], reals[1], reals[2]));
                                break;

                            case 	's':
                                current_material->set_Ks(
                                        RGBColor(reals[0], reals[1], reals[2]));
                                break;

                            default:
                                assert(false);
                                break;
                        }

                        break;

                    case 'm':
                        if (buffer[1] == 'a' &&
                                buffer[2] == 'p' &&
                                buffer[3] == '_') {
                            switch (buffer[4]) {
                                case 'K':
                                    switch (buffer[5]) {
                                        case 'a':
                                            c = &buffer[7];
                                            assert(*c != '-');
                                            for (; *c != '\0' && c - &buffer[7] < 93; ++c);

                                            current_material->set_map_Ka_filename(
                                                    std::string(&buffer[7], c));
                                            break;

                                        case 'd':
                                            c = &buffer[7];
                                            assert(*c != '-');
                                            for (; *c != '\0' && c - &buffer[7] < 93; ++c);

                                            current_material->set_map_Kd_filename(
                                                    std::string(&buffer[7], c));
                                            break;

                                        case 's':
                                            c = &buffer[7];
                                            assert(*c != '-');
                                            for (; *c != '\0' && c - &buffer[7] < 93; ++c);

                                            current_material->set_map_Ks_filename(
                                                    std::string(&buffer[7], c));
                                            break;

                                        default:
                                            break;
                                    }

                                    break;

                                default:
                                    assert(false);
                                    break;
                            }
                        }

                        break;

                    case 'n':
                        if (buffer[1] == 'e' &&
                                buffer[2] == 'w' &&
                                buffer[3] == 'm' &&
                                buffer[4] == 't' &&
                                buffer[5] == 'l') {
                            ++count;

                            if (current_material != 0) {
                                if (manager.getMaterial(material_name) ==
                                        MaterialManager::NULL_MATERIAL_POINTER) {
                                    manager.setMaterial(
                                            material_name, current_material);
                                }
                            }

                            char* c = &buffer[7];

                            for (; *c != '\0' && c - &buffer[7] < 93; ++c);

                            material_name.assign(&buffer[7], c);

                            current_material = std::shared_ptr<Material>(
                                    new Material());
                            current_material->setName(material_name);
                        }

                        break;

                    case 'N':
                        if (buffer[1] == 'i') {
                            Real Ni;
                            int pos = 3;

                            Utility::read_float(buffer.get(), 100, pos, Ni);
                            current_material->set_Ni(Ni);
                        } else {
                            assert(false);
                        }

                        break;

                    case 'T':
                        if (buffer[1] == 'f') {
                            pos = 3;

                            for (int unsigned i = 0; i < 3; ++i) {
                                Utility::read_float(buffer.get(), 100, pos, reals[i]);
                                ++pos;
                            }
                        } else {
                            assert(false);
                        }

                        current_material->set_Tf(
                                RGBColor(reals[0], reals[1], reals[2]));
                        break;

                    default:
                        break;
                }
            }

            manager.setMaterial(material_name, current_material);
        } else {
            std::cout << filename << std::endl << "\t...not opened!\n";
        }
    }
}