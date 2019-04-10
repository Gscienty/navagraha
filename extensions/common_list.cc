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

}
}
