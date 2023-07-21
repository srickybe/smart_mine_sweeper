#include "MaterialManager.h"
#include <cassert>
#include <iostream>

namespace ngn {
    MaterialManager::ptr_t const MaterialManager::NULL_MATERIAL_POINTER;

    MaterialManager::MaterialManager()
    : materials_() {
    }

    void MaterialManager::getMaterialNames(std::vector< std::string > & names)const {
        if (!materials_.empty()) {
            const_iterator it = materials_.begin(),
                    end = materials_.end();

            for (; it != end; ++it) {
                names.push_back(it->first);
            }
        }
    }

    MaterialManager::ptr_t const &
    MaterialManager::getMaterial(std::string const & name)const {
        MaterialManager::const_iterator it = materials_.find(name),
                end = materials_.end();

        if (it != end) {
            return it->second;
        }

        return MaterialManager::NULL_MATERIAL_POINTER;
    }

    void MaterialManager::setMaterial(std::string const & name,
            MaterialManager::ptr_t & pMaterial) {
        assert(materials_.find(name) == materials_.end());
        assert(pMaterial != 0);

        assert(materials_.insert(MaterialManager::value_t(name, pMaterial)).second);
    }

    void MaterialManager::info(std::ostream & out)const {
        if (!materials_.empty()) {
            MaterialManager::const_iterator it = materials_.begin(),
                    end = materials_.end();

            for (; it != end; ++it) {
                out << "material:\n";
                it->second->info(out);
                out << "\n";
            }
        }
    }
}
