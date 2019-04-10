#include "kubeent/sysctl.hpp"

namespace navagraha {
namespace kubeent {

char SYSCTL_NAME[] = "name";
char SYSCTL_VALUE[] = "value";

void sysctl::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name)
        .add(this->value);
}

}
}
