#include "kubeent/resource_requirements.hpp"

namespace navagraha {
namespace kubeent {

char RESOURCE_REQUIREMENTS_LIMITS[] = "limits";
char RESOURCE_REQUIREMENTS_REQUESTS[] = "requests";

void resource_requirements::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->limits)
        .add(this->requests);
}

}
}
