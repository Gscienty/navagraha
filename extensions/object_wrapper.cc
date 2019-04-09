#include "extensions/object_wrapper.hpp"
#include "extensions/field.hpp"

namespace navagraha {
namespace extensions {

void object_wrapper::serialize(object_wrapper & obj, std::ostringstream & str)
{
    if (obj.serializer) {
        obj.serializer(str);
    }
    else {
        str.write("{}", 2);
    }
}

object_wrapper & object_wrapper::serialized_self()
{
    this->serializer = std::bind(&absobj_field_value::serialize,
                                 this->obj,
                                 std::placeholders::_1);
    return *this;
}

void object_wrapper::serialize(std::ostringstream & str)
{
    object_wrapper::serialize(*this, str);
}

void object_wrapper::deserialize(object_wrapper & obj, std::istringstream & str)
{
    extensions::serializer<absobj_field_value>::deserialize(obj.obj, str);
}

void object_wrapper::deserialize(std::istringstream & str)
{
    object_wrapper::deserialize(*this, str);
}

}
}
