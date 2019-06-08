#ifndef _NAVAGRAHA_KUBEENT_CRON_JOB_SPEC_H
#define _NAVAGRAHA_KUBEENT_CRON_JOB_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/job_template_spec.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CRON_JOB_SPEC_CONCURRENCY_POLICY[];
extern char CRON_JOB_SPEC_FAILED_JOBS_HISTORY_LIMIT[];
extern char CRON_JOB_SPEC_JOB_TEMPLATE[];
extern char CRON_JOB_SPEC_SCHEDULE[];
extern char CRON_JOB_SPEC_STARTING_DEADLINE_SECONDS[];
extern char CRON_JOB_SPEC_SUCCESSFUL_JOBS_HISTORY_LIMIT[];
extern char CRON_JOB_SPEC_SUSPEND[];

class cron_job_spec : public extensions::serializable<cron_job_spec> {
public:
    extensions::field<std::string, CRON_JOB_SPEC_CONCURRENCY_POLICY> concurrency_policy;
    extensions::field<int, CRON_JOB_SPEC_FAILED_JOBS_HISTORY_LIMIT> failed_jobs_history_limit;
    extensions::field<job_template_spec, CRON_JOB_SPEC_JOB_TEMPLATE> job_template;
    extensions::field<std::string, CRON_JOB_SPEC_SCHEDULE> schedule;
    extensions::field<int, CRON_JOB_SPEC_STARTING_DEADLINE_SECONDS> starting_deadline_seconds;
    extensions::field<int, CRON_JOB_SPEC_SUCCESSFUL_JOBS_HISTORY_LIMIT> successful_jobs_history_limit;
    extensions::field<bool, CRON_JOB_SPEC_SUSPEND> suspend;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
