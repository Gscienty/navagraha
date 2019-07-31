#include "kubeent/limit_range_spec.hpp"

namespace navagraha {
namespace kubeent {

char LIMIT_RANGE_SPEC_LIMITS[] = "limits";

void limit_range_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->limits);
}

}
}
