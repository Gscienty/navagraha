#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace extensions {

link_serializer::link_serializer(link_serializer_type type)
    : _type(type)
{

}

char link_serializer::begin_brackets() const {
    if (this->_type == link_serializer_type::list) {
        return '[';
    }
    else {
        return '{';
    }
}

char link_serializer::end_brackets() const
{
    if (this->_type == link_serializer_type::list) {
        return ']';
    }
    else {
        return '}';
    }
}

void link_serializer::serialize(std::ostringstream & str)
{
    str.put(this->begin_brackets());
    fields_serialize(this->_serializers, str);
    str.put(this->end_brackets());
}

void link_serializer::deserialize(std::istringstream & str)
{
    std::ostringstream key_str;
    while (str.peek() != this->end_brackets()) {
        key_str.str("");
        while (str.peek() != '"' && str.peek() != this->end_brackets()) {
            str.get();
        }
        if (str.peek() == this->end_brackets()) {
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
    str.get();
}

}
}
