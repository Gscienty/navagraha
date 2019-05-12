#include "kubeent/job.hpp"

namespace navagraha {
namespace kubeent {

char JOB_API_VERSION[] = "apiVersion";
char JOB_KIND[] = "kind";
char JOB_METADATA[] = "metadata";
char JOB_SPEC[] = "spec";
char JOB_STATUS[] = "status";

void job::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->kind)
        .add(this->metadata)
        .add(this->spec)
        .add(this->status);
}

}
}
