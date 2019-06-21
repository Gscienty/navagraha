#ifndef _NAVAGRAHA_EXTENSION_COMMON_LIST_H
#define _NAVAGRAHA_EXTENSION_COMMON_LIST_H

#include <list>
#include <functional>
#include <sstream>
#include "extensions/field.hpp"
#include "extensions/special_abstract_object.hpp"

namespace navagraha {
namespace extensions {

class common_list : public special_abstract_object<common_list, abstract_object_type_list> {
public:
    std::vector<abstract_object> & values();

    common_list & serialize(std::ostringstream & str);

    common_list & deserialize(std::istringstream & str);

    static common_list to_special(abstract_object & obj);

    static common_list deserialize(const std::string & payload);
};

}
}

#endif
