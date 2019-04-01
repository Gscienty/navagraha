#include "kubecil/initializers.hpp"

namespace navagraha {
namespace kubecil {

char INITIALIZERS_PENDING[] = "pending";

void initializers::serialize(initializers & obj, std::ostringstream & str)
{
    extensions::link_serializer(extensions::link_serializer_type::object)
        .add(obj.pending)
        .serialize(str);
}

}
}
