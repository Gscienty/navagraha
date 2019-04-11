#ifndef _NAVAGRAHA_KUBEENT_POD_CONDITION_H
#define _NAVAGRAHA_KUBEENT_POD_CONDITION_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/time.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char POD_CONDITION_LAST_PROBE_TIME[];
extern char POD_CONDITION_LAST_TRANSITION_TIME[];
extern char POD_CONDITION_MESSAGE[];
extern char POD_CONDITION_REASON[];
extern char POD_CONDITION_STATUS[];
extern char POD_CONDITION_TYPE[];

class pod_condition : public serializable<pod_condition> {
public:
    extensions::field<time, POD_CONDITION_LAST_PROBE_TIME> last_probe_time;
    extensions::field<time, POD_CONDITION_LAST_TRANSITION_TIME> last_transition_time;
    extensions::field<std::string, POD_CONDITION_MESSAGE> message;
    extensions::field<std::string, POD_CONDITION_REASON> reason;
    extensions::field<std::string, POD_CONDITION_STATUS> status;
    extensions::field<std::string, POD_CONDITION_TYPE> type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
