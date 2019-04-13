#ifndef _NAVAGRAHA_KUBEENT_REPLICATION_CONTROLLER_CONDITION_H
#define _NAVAGRAHA_KUBEENT_REPLICATION_CONTROLLER_CONDITION_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/time.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char REPLICATION_CONTROLLER_CONDITION_LAST_TRANSITION_TIME[];
extern char REPLICATION_CONTROLLER_CONDITION_MESSAGE[];
extern char REPLICATION_CONTROLLER_CONDITION_REASON[];
extern char REPLICATION_CONTROLLER_CONDITION_STATUS[];
extern char REPLICATION_CONTROLLER_CONDITION_TYPE[];

class replication_controller_condition : public serializable<replication_controller_condition> {
public:
    extensions::field<time, REPLICATION_CONTROLLER_CONDITION_LAST_TRANSITION_TIME> last_transition_time;
    extensions::field<std::string, REPLICATION_CONTROLLER_CONDITION_MESSAGE> message;
    extensions::field<std::string, REPLICATION_CONTROLLER_CONDITION_REASON> reason;
    extensions::field<std::string, REPLICATION_CONTROLLER_CONDITION_STATUS> status;
    extensions::field<std::string, REPLICATION_CONTROLLER_CONDITION_TYPE> type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
