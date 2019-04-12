#include "kubeent/cron_job.hpp"

namespace navagraha {
namespace kubeent {

char CRON_JOB_API_VERSION[] = "apiVersion";
char CRON_JOB_KIND[] = "kind";
char CRON_JOB_METADATA[] = "metadata";
char CRON_JOB_SPEC[] = "spec";
char CRON_JOB_STATUS[] = "status";

void cron_job::bind(extensions::serializer_helper & helper)
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
