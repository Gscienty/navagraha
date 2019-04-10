#include "kubeent/capabilities.hpp"

namespace navagraha {
namespace kubeent {

char CAPABILITIES_ADD[] = "add";
char CAPABILITIES_DROP[] = "drop";

void capabilities::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->add)
        .add(this->drop);
}

capabilities & capabilities::serialize(std::ostringstream & str)
{
    return *extensions::serializer_helper()
        .serialize(&capabilities::bind, this, str);
}

capabilities & capabilities::deserialize(std::istringstream & str)
{
    return *extensions::serializer_helper()
        .deserialize(&capabilities::bind, this, str);
}
extensions::abstract_object capabilities::to_abstract()
{
    return extensions::serializer_helper()
        .to_abstract(&capabilities::bind, this);
}
capabilities capabilities::to_special(extensions::abstract_object & obj)
{
    return extensions::serializer_helper()
        .to_special(&capabilities::bind, capabilities(), obj);
}

}
}
