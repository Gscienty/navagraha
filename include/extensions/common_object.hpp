#ifndef _NAVAGRAHA_EXTENSION_COMMON_OBJECT_H
#define _NAVAGRAHA_EXTENSION_COMMON_OBJECT_H

#include "extensions/field.hpp"
#include "extensions/special_abstract_object.hpp"
#include <functional>
#include <sstream>
#include <string>
#include <map>

namespace navagraha {
namespace extensions {

class common_object : public special_abstract_object<common_object, abstract_object_type_obj> {
public:
    std::map<std::string, abstract_object> & values();

    template <typename T_Field> common_object & operator= (T_Field & field)
    {
        this->obj() = serializer<T_Field>::to_abstract(field);
    }

    common_object & serialize(std::ostringstream & str);

    common_object & deserialize(std::istringstream & str);

    static common_object to_special(abstract_object & obj);
};

}
}

#endif
