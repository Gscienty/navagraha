#include "kubecli/initializers.hpp"

namespace navagraha {
namespace kubectl {

char INITIALIZERS_PENDING[] = "pending";

void initializers::serialize(initializers & obj, std::ostringstream & str)
{
    std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> serializers = {
        extensions::field_serializer(obj.pending)
    };

    str.put('{');
    extensions::fields_serialize(serializers, str);
    str.put('}');
}

}
}
