#include "extensions/common_list.hpp"

namespace navagraha {
namespace extensions {

std::vector<abstract_object> & common_list::values()
{
    return this->obj().list;
}

common_list common_list::to_special(abstract_object & obj)
{
    common_list ret;
    ret.obj() = obj;
    return ret;
}

common_list & common_list::serialize(std::ostringstream & str)
{
    this->abstract_serialize(str);
    return *this;
}

common_list & common_list::deserialize(std::istringstream & str)
{
    this->abstract_deserialize(str);
    return *this;
}

}
}
