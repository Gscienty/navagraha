#include "extensions/list_wrapper.hpp"
#include <algorithm>

namespace navagraha {
namespace extensions {


void list_wrapper::serialize(list_wrapper & obj, std::ostringstream & str)
{
    bool is_first = false;
    str.put('[');
    std::for_each(obj.serializers.begin(),
                  obj.serializers.end(),
                  [&] (std::function<void (std::ostringstream &)> & func) -> void
                  {
                        if (is_first) {
                            str.put(',');
                        }
                        func(str);
                        is_first = true;
                  });
    str.put(']');
}

}
}
