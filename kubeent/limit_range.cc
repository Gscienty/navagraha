#include "kubeent/limit_range.hpp"

namespace navagraha {
namespace kubeent {

char LIMIT_RANGE_API_VERSION[] = "apiVersion";
char LIMIT_RANGE_KIND[] = "kind";
char LIMIT_RANGE_METADATA[] = "metadata";
char LIMIT_RANGE_SPEC[] = "spec";

void limit_range::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->kind)
        .add(this->metadata)
        .add(this->spec);
}

}
}
