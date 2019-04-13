#include "kubeent/endpoints.hpp"

namespace navagraha {
namespace kubeent {

char ENDPOINTS_API_VERSION[] = "apiVersion";
char ENDPOINTS_KIND[] = "kind";
char ENDPOINTS_METADATA[] = "metadata";
char ENDPOINTS_SUBSETS[] = "subsets";

void endpoints::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->kind)
        .add(this->metadata)
        .add(this->subsets);
}

}
}
