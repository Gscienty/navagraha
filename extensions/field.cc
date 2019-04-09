#include "extensions/field.hpp"
#include <algorithm>
#include <sstream>

namespace navagraha {
namespace extensions {

absobj_field_value::absobj_field_value(int val) : type(absobj_field_type_num)
{
    this->val.num = val;
}

absobj_field_value::absobj_field_value(bool val) : type(absobj_field_type_boolean)
{
    this->val.boolean = val;
}

absobj_field_value::absobj_field_value(const char * const val) : type(absobj_field_type_str)
{
    this->str = val;
}

absobj_field_value::absobj_field_value(std::string val) : type(absobj_field_type_str)
{
    this->str = val;
}

absobj_field_value::absobj_field_value() : type(absobj_field_type_obj)
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

absobj_field_value & absobj_field_value::self_serialize(std::ostringstream & str)
{
    absobj_field_value::serialize(*this, str);
    return *this;
}

absobj_field_value & absobj_field_value::self_deserialize(std::istringstream & str)
{
    absobj_field_value::deserialize(*this, str);
    return *this;
}

}
}
