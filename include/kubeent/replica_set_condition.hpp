#ifndef _NAVAGRAHA_KUBEENT_REPLICA_SET_CONDITION_H
#define _NAVAGRAHA_KUBEENT_REPLICA_SET_CONDITION_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/time.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char REPLICA_SET_CONDITION_LAST_TRANSITION_TIME[];
extern char REPLICA_SET_CONDITION_MESSAGE[];
extern char REPLICA_SET_CONDITION_REASON[];
extern char REPLICA_SET_CONDITION_STATUS[];
extern char REPLICA_SET_CONDITION_TYPE[];

class replica_set_condition : public extensions::serializable<replica_set_condition> {
public:
    extensions::field<time, REPLICA_SET_CONDITION_LAST_TRANSITION_TIME> last_transition_time;
    extensions::field<std::string, REPLICA_SET_CONDITION_MESSAGE> message;
    extensions::field<std::string, REPLICA_SET_CONDITION_REASON> reason;
    extensions::field<std::string, REPLICA_SET_CONDITION_STATUS> status;
    extensions::field<std::string, REPLICA_SET_CONDITION_TYPE> type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
