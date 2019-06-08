#ifndef _NAVAGRAHA_KUBEENT_JOB_CONDITION_H
#define _NAVAGRAHA_KUBEENT_JOB_CONDITION_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/time.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char JOB_CONDITION_LAST_PROBE_TIME[];
extern char JOB_CONDITION_LAST_TRANSITION_TIME[];
extern char JOB_CONDITION_MESSAGE[];
extern char JOB_CONDITION_REASON[];
extern char JOB_CONDITION_STATUS[];
extern char JOB_CONDITION_TYPE[];

class job_condition : public extensions::serializable<job_condition> {
public:
    extensions::field<time, JOB_CONDITION_LAST_PROBE_TIME> last_probe_time;
    extensions::field<time, JOB_CONDITION_LAST_TRANSITION_TIME> last_transition_time;
    extensions::field<std::string, JOB_CONDITION_MESSAGE> message;
    extensions::field<std::string, JOB_CONDITION_REASON> reason;
    extensions::field<std::string, JOB_CONDITION_STATUS> status;
    extensions::field<std::string, JOB_CONDITION_TYPE> type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
