#include "kubecli/initializer.hpp"

namespace navagraha {
namespace kubectl {

char INITIALIZERS_NAME[] = "name";

void initializer::serialize(initializer & obj, std::ostringstream & str)
{
    std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> serializers = {
        extensions::field_serializer(obj.name)
    };

    str.put('{');
    extensions::fields_serialize(serializers, str);
    str.put('}');
}

}
}
