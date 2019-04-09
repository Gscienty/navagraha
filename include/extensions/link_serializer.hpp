#ifndef _NAVAGRAHA_EXTENSION_LINK_SERIALIZER_H
#define _NAVAGRAHA_EXTENSION_LINK_SERIALIZER_H

#include <list>
#include <functional>
#include <sstream>
#include <map>
#include "extensions/field.hpp"

namespace navagraha {
namespace extensions {

enum link_serializer_type {
    link_serializer_type_serialize,
    link_serializer_type_deserialize,
    link_serializer_type_to_abstract
};

class link_serializer {
private:
    link_serializer_type _type;
    std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> _serializers;
    std::map<std::string, std::function<void (std::istringstream &)>> _deserializers;
    abstract_object _absobj; 
public:
    link_serializer(link_serializer_type type = link_serializer_type_serialize);

    template <typename T_Field> link_serializer & add(T_Field & field)
    {
        switch (this->_type) {
        case link_serializer_type_serialize:
            this->_serializers.push_back(field_serializer(field));
            break;
        case link_serializer_type_deserialize:
            this->_deserializers.insert(field_deserialize(field));
            break;
        case link_serializer_type_to_abstract:
            this->_absobj.obj[field.key] = field.get();
            break;
        }
        return *this;
    }

    void serialize(std::ostringstream & str);
    void deserialize(std::istringstream & str);
    abstract_object to_abstract();
};

}
}

#endif
