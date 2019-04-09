#include "extensions/list_wrapper.hpp"
#include <algorithm>

namespace navagraha {
namespace extensions {

list_wrapper::list_wrapper()
{
    this->_list.type = absobj_field_type_list;
}

std::vector<absobj_field_value> & list_wrapper::values()
{
    return this->_list.list;
}

void list_wrapper::serialize(list_wrapper & obj, std::ostringstream & str)
{
    serializer<absobj_field_value>::serialize(obj._list, str);
}

list_wrapper & list_wrapper::serialize(std::ostringstream & str)
{
    list_wrapper::serialize(*this, str);
    return *this;
}

}
}
