#include "extensions/common_list.hpp"
#include <algorithm>

namespace navagraha {
namespace extensions {

std::vector<abstract_object> & common_list::values()
{
    return this->obj().list;
}

}
}
