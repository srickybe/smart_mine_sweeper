#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include <iosfwd>
#include <map>
#include <memory>
#include <vector>
#include "Material.h"


namespace ngn {

    class MaterialManager {
    public:
        typedef std::shared_ptr< Material > ptr_t;

        static ptr_t const NULL_MATERIAL_POINTER;

        MaterialManager();

        void getMaterialNames(std::vector< std::string > &)const;
        MaterialManager::ptr_t const & getMaterial(std::string const &)const;
        void setMaterial(std::string const &, MaterialManager::ptr_t &);

        void info(std::ostream &)const;

    private:
        typedef std::map< std::string, ptr_t > map_t;
        typedef map_t::const_iterator const_iterator;
        typedef map_t::value_type value_t;
        map_t materials_;
    };
}

#endif // MATERIAL_MANAGER_H
