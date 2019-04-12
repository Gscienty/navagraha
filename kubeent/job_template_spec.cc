#include "kubeent/job_template_spec.hpp"

namespace navagraha {
namespace kubeent {

char JOB_TEMPLATE_SPEC_METADATA[] = "metadata";
char JOB_TEMPLATE_SPEC_SPEC[] = "spec";

void job_template_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->metadata)
        .add(this->spec);
}

}
}
