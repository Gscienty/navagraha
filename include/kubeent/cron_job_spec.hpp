#ifndef _NAVAGRAHA_KUBEENT_CRON_JOB_SPEC_H
#define _NAVAGRAHA_KUBEENT_CRON_JOB_SPEC_H

#include "extensions/field.hpp"

namespace navagraha {
namespace kubeent {

extern char CRON_JOB_SPEC_CONCURRENCY_POLICY[];
extern char CRON_JOB_SPEC_FAILED_JOBS_HISTORY_LIMIT[];
extern char CRON_JOB_SPEC_JOB_TEMPLATE[];
extern char CRON_JOB_SPEC_SCHEDULE[];
extern char CRON_JOB_SPEC_STARTING_DEADLINE_SECONDS[];
extern char CRON_JOB_SPEC_SUCCESS_FUL_JOBS_HISTORY_LIMIT[];
extern char CRON_JOB_SPEC_SUSPEND[];

class cron_job_spec {

};

}
}

#endif
