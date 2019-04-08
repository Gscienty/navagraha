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
    object,
    list
};

class link_serializer {
private:
    link_serializer_type _type;
    std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> _serializers;
    std::map<std::string, std::function<void (std::istringstream &)>> _deserializers;
public:
    link_serializer(link_serializer_type type = link_serializer_type::object);

    template <typename T_Field> link_serializer & add(T_Field & field)
    {
        this->_serializers.push_back(field_serializer(field));
        this->_deserializers.insert(field_deserialize(field));
        return *this;
    }

    char begin_brackets() const;
    char end_brackets() const;

    void serialize(std::ostringstream & str);
    void deserialize(std::istringstream & str);
};

}
}

#endif
