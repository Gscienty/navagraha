#include "kubeent/cron_job_spec.hpp"

namespace navagraha {
namespace kubeent {

char CRON_JOB_SPEC_CONCURRENCY_POLICY[] = "concurrencyPolicy";
char CRON_JOB_SPEC_FAILED_JOBS_HISTORY_LIMIT[] = "failedJobsHistoryLimit";
char CRON_JOB_SPEC_JOB_TEMPLATE[] = "jobTemplate";
char CRON_JOB_SPEC_SCHEDULE[] = "schedule";
char CRON_JOB_SPEC_STARTING_DEADLINE_SECONDS[] = "startingDeadlineSeconds";
char CRON_JOB_SPEC_SUCCESSFUL_JOBS_HISTORY_LIMIT[] = "successfulJobsHistoryLimit";
char CRON_JOB_SPEC_SUSPEND[] = "suspend";

void cron_job_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->concurrency_policy)
        .add(this->failed_jobs_history_limit)
        .add(this->job_template)
        .add(this->schedule)
        .add(this->starting_deadline_seconds)
        .add(this->successful_jobs_history_limit)
        .add(this->suspend);
}

}
}
