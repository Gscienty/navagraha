#include "kubeent/cron_job_status.hpp"

namespace navagraha {
namespace kubeent {

char CRON_JOB_SPEC_ACTIVE[] = "active";
char CRON_JOB_SPEC_LAST_SCHEDULE_TIME[] = "lastScheduleTime";

void cron_job_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->active)
        .add(this->last_schedule_time);
}

}
}
