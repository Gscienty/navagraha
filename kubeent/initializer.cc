#include "kubeent/initializer.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char INITIALIZERS_NAME[] = "name";

void initializer::serialize(initializer & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.name)
        .serialize(str);
}

}
}
