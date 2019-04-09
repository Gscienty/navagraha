#include "extensions/field.hpp"
#include <algorithm>
#include <sstream>

namespace navagraha {
namespace extensions {

absobj_field_value::absobj_field_value(int val) : type(absobj_field_type::num)
{
    this->val.num = val;
}

absobj_field_value::absobj_field_value(bool val) : type(absobj_field_type::boolean)
{
    this->val.boolean = val;
}

absobj_field_value::absobj_field_value(const char * const val) : type(absobj_field_type::str)
{
    this->str = val;
}

absobj_field_value::absobj_field_value(std::string val) : type(absobj_field_type::str)
{
    this->str = val;
}

absobj_field_value::absobj_field_value() : type(absobj_field_type::obj)
{

}

void absobj_field_value::serialize(absobj_field_value & obj, std::ostringstream & str)
{
    serializer<absobj_field_value>::serialize(obj, str);
}

void absobj_field_value::deserialize(absobj_field_value & obj, std::istringstream & str)
{
    serializer<absobj_field_value>::deserialize(obj, str);
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

}
}
