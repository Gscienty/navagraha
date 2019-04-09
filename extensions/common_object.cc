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

}
}
