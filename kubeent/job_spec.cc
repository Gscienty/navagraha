#include "kubeent/job_spec.hpp"

namespace navagraha {
namespace kubeent {

char JOB_SPEC_ACTIVE_DEADLINE_SECONDS[] = "activeDeadlineSeconds";
char JOB_SPEC_BACKOFF_LIMIT[] = "backoffLimit";
char JOB_SPEC_COMPLETIONS[] = "completions";
char JOB_SPEC_MANUAL_SELECTOR[] = "manualSelector";
char JOB_SPEC_PARALLELISM[] = "parallelism";
char JOB_SPEC_SELECTOR[] = "selector";
char JOB_SPEC_TEMPLATE[] = "template";
char JOB_SPEC_TTL_SECONDS_AFTER_FINISHED[] = "ttlSecondsAfterFinished";

void job_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->active_deadline_seconds)
        .add(this->backoff_limit)
        .add(this->completions)
        .add(this->manual_selector)
        .add(this->parallelism)
        .add(this->selector)
        .add(this->template_)
        .add(this->ttl_seconds_after_finished);
}

}
}
