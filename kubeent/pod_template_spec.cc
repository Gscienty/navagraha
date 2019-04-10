#include "kubeent/pod_template_spec.hpp"

namespace navagraha {
namespace kubeent {

char POD_TEMPLATE_SPEC_METADATA[] = "metadata";
char POD_TEMPLATE_SPEC_SPEC[] = "spec";

void pod_template_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->metadata)
        .add(this->spec);
}

}
}
