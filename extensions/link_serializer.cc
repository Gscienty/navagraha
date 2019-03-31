#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace extensions {

link_serializer::link_serializer(link_serializer_type type)
    : _type(type)
{

}

void link_serializer::serialize(std::ostringstream & str)
{
    if (this->_type == link_serializer_type::link_serializer_type_list) {
        str.put('[');
    }
    else {
        str.put('{');
    }
    fields_serialize(this->_serializers, str);
    if (this->_type == link_serializer_type::link_serializer_type_list) {
        str.put(']');
    }
    else {
        str.put('}');
    }
}

}
}
