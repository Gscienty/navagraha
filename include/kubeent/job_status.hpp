#ifndef _NAVAGRAHA_KUBEENT_JOB_STATUS_H
#define _NAVAGRAHA_KUBEENT_JOB_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/time.hpp"
#include "kubeent/job_condition.hpp"

namespace navagraha {
namespace kubeent {

extern char JOB_STATUS_ACTIVE[];
extern char JOB_STATUS_COMPLETION_TIME[];
extern char JOB_STATUS_CONDITIONS[];
extern char JOB_STATUS_FAILED[];
extern char JOB_STATUS_START_TIME[];
extern char JOB_STATUS_SUCCEEDED[];

class job_status : public extensions::serializable<job_status> {
public:
    extensions::field<int, JOB_STATUS_ACTIVE> active;
    extensions::field<time, JOB_STATUS_COMPLETION_TIME> completion_time;
    extensions::field<extensions::special_list<job_condition>, JOB_STATUS_CONDITIONS> conditions;
    extensions::field<int, JOB_STATUS_FAILED> failed;
    extensions::field<time, JOB_STATUS_START_TIME> start_time;
    extensions::field<int, JOB_STATUS_SUCCEEDED> succeeded;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
