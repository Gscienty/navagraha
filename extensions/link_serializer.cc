#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace extensions {

link_serializer::link_serializer(link_serializer_type type)
    : _type(type)
{

}

void link_serializer::serialize(std::ostringstream & str)
{
    if (this->_type != link_serializer_type_serialize) {
        return;
    }
    str.put('{');
    fields_serialize(this->_serializers, str);
    str.put('}');
}

void link_serializer::deserialize(std::istringstream & str)
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

abstract_object link_serializer::to_abstract()
{
    return this->_absobj;
}

}
}
