#include "extensions/field.hpp"
#include <algorithm>
#include <sstream>

namespace navagraha {
namespace extensions {

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
