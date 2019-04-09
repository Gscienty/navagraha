#include "extensions/common_object.hpp"
#include "extensions/field.hpp"

namespace navagraha {
namespace extensions {

std::map<std::string, abstract_object> & common_object::values()
{
    return this->obj().obj;
}

}
}
