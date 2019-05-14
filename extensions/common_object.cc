#include "extensions/common_object.hpp"
#include "extensions/field.hpp"

namespace navagraha {
namespace extensions {

std::map<std::string, abstract_object> & common_object::values()
{
    return this->obj().obj;
}

common_object common_object::to_special(abstract_object & obj)
{
    common_object ret;
    ret.obj() = obj;
    return ret;
}

common_object & common_object::serialize(std::ostringstream & str)
{
    this->abstract_serialize(str);
    return *this;
}

common_object & common_object::deserialize(std::istringstream & str)
{
    this->abstract_deserialize(str);
    return *this;
}

common_object common_object::deserialize(std::string & payload)
{
    if (payload.length() == 0) {
        payload = "{}";
    }
    std::istringstream str(payload);
    common_object obj;

    obj.deserialize(str);
    return obj;
}

}
}
