#include "kubecil/initializer.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubecil {

char INITIALIZERS_NAME[] = "name";

void initializer::serialize(initializer & obj, std::ostringstream & str)
{
    extensions::link_serializer(extensions::link_serializer_type::object)
        .add(obj.name)
        .serialize(str);
}

}
}
