#include "kubeent/job_status.hpp"

namespace navagraha {
namespace kubeent {

char JOB_STATUS_ACTIVE[] = "active";
char JOB_STATUS_COMPLETION_TIME[] = "completionTime";
char JOB_STATUS_CONDITIONS[] = "conditions";
char JOB_STATUS_FAILED[] = "failed";
char JOB_STATUS_START_TIME[] = "startTime";
char JOB_STATUS_SUCCEEDED[] = "succeeded";

void job_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->active)
        .add(this->completion_time)
        .add(this->conditions)
        .add(this->failed)
        .add(this->start_time)
        .add(this->succeeded);
}

}
}
