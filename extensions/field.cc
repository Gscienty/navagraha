#include "extensions/field.hpp"
#include <algorithm>
#include <sstream>

namespace navagraha {
namespace extensions {

abstract_object::abstract_object(int val) : type(abstract_object_type_num)
{
    this->val.num = val;
}

abstract_object::abstract_object(bool val) : type(abstract_object_type_boolean)
{
    this->val.boolean = val;
}

abstract_object::abstract_object(const char * const val) : type(abstract_object_type_str)
{
    this->str = val;
}

abstract_object::abstract_object(std::string val) : type(abstract_object_type_str)
{
    this->str = val;
}

abstract_object::abstract_object() : type(abstract_object_type_obj)
{

}

void fields_serialize(std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> & serializers,
                      std::ostringstream & str)
{
    bool has_serialized = false;

    std::for_each(serializers.begin(), serializers.end(),
                  [&] (std::pair<bool, std::function<void (std::ostringstream &)>> & inner_field) {
                        if (inner_field.first) {
                            if (has_serialized) {
                                str.put(',');
                            }
                            has_serialized = true;
                            inner_field.second(str);
                        }
                  });

}

abstract_object & abstract_object::serialize(std::ostringstream & str)
{
    serializer<abstract_object>::serialize(*this, str);
    return *this;
}

abstract_object & abstract_object::deserialize(std::istringstream & str)
{
    serializer<abstract_object>::deserialize(*this, str);
    return *this;
}
abstract_object abstract_object::to_abstract()
{
    return *this;
}

}
}
