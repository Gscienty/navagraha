#include "extensions/serializer_helper.hpp"

namespace navagraha {
namespace extensions {

serializer_helper::serializer_helper(link_serializer_type type)
    : _type(type)
{

}

void serializer_helper::serialize(std::ostringstream & str)
{
    if (this->_type != link_serializer_type_serialize) {
        return;
    }
    str.put('{');
    fields_serialize(this->_serializers, str);
    str.put('}');
}

void serializer_helper::deserialize(std::istringstream & str)
{
    if (this->_type != link_serializer_type_deserialize) {
        return;
    }
    std::ostringstream key_str;
    while (str.peek() != '}') {
        key_str.str("");
        while (str.peek() != '"' && str.peek() != '}') {
            str.get();
        }
        if (str.peek() == '}') {
            break;
        }
        str.get();
        while(str.peek() != '"') {
            key_str.put(str.get());
        }

        auto deserialize_iter = this->_deserializers.find(key_str.str());
        if (deserialize_iter != this->_deserializers.end()) {
            deserialize_iter->second(str);
        }
    }
}

abstract_object serializer_helper::to_abstract()
{
    return this->_absobj;
}

}
}
