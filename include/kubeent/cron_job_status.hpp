#ifndef _NAVAGRAHA_KUBEENT_CRON_JOB_STATUS_H
#define _NAVAGRAHA_KUBEENT_CRON_JOB_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/object_reference.hpp"
#include "kubeent/time.hpp"

namespace navagraha {
namespace kubeent {

extern char CRON_JOB_SPEC_ACTIVE[];
extern char CRON_JOB_SPEC_LAST_SCHEDULE_TIME[];

class cron_job_status : public extensions::serializable<cron_job_status> {
public:
    extensions::field<
        extensions::special_list<object_reference>,
        CRON_JOB_SPEC_ACTIVE> active;
    extensions::field<time, CRON_JOB_SPEC_LAST_SCHEDULE_TIME> last_schedule_time;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
