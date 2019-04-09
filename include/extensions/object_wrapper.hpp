#ifndef _NAVAGRAHA_EXTENSION_OBJECT_WRAPPER_H
#define _NAVAGRAHA_EXTENSION_OBJECT_WRAPPER_H

#include "extensions/field.hpp"
#include <functional>
#include <sstream>
#include <string>
#include <map>

namespace navagraha {
namespace extensions {

class object_wrapper {
public:
    std::function<void (std::ostringstream &)> serializer;
    absobj_field_value obj;

    template <typename T_Field> object_wrapper & operator= (T_Field & field)
    {
        this->serializer = std::bind(&T_Field::serialize,
                                     field,
                                     std::placeholders::_1);
    }

    object_wrapper & serialized_self();

    static void serialize(object_wrapper & obj, std::ostringstream & str);

    void serialize(std::ostringstream & str);

    static void deserialize(object_wrapper & obj, std::istringstream & str);

    void deserialize(std::istringstream & str);
};

}
}

#endif
