#ifndef _NAVAGRAHA_KUBEENT_NODE_CONDITION_H
#define _NAVAGRAHA_KUBEENT_NODE_CONDITION_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/time.hpp"

namespace navagraha {
namespace kubeent {

extern char NODE_CONDITION_LAST_HEARTBEAT_TIME[];
extern char NODE_CONDITION_LAST_TRANSITION_TIME[];
extern char NODE_CONDITION_MESSAGE[];
extern char NODE_CONDITION_REASON[];
extern char NODE_CONDITION_STATUS[];
extern char NODE_CONDITION_TYPE[];

class node_condition : public extensions::serializable<node_condition> {
public:
    extensions::field<time, NODE_CONDITION_LAST_HEARTBEAT_TIME> last_heartbeat_time;
    extensions::field<time, NODE_CONDITION_LAST_TRANSITION_TIME> last_transition_time;
    extensions::field<std::string, NODE_CONDITION_MESSAGE> message;
    extensions::field<std::string, NODE_CONDITION_REASON> reason;
    extensions::field<std::string, NODE_CONDITION_STATUS> status;
    extensions::field<std::string, NODE_CONDITION_TYPE> type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
