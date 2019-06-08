#ifndef _NAVAGRAHA_KUBEENT_STATEFUL_SET_STATUS_H
#define _NAVAGRAHA_KUBEENT_STATEFUL_SET_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/stateful_set_condition.hpp"

namespace navagraha {
namespace kubeent {

extern char STATEFUL_SET_STATUS_COLLISION_COUNT[];
extern char STATEFUL_SET_STATUS_CONDITIONS[];
extern char STATEFUL_SET_STATUS_CURRENT_REPLICAS[];
extern char STATEFUL_SET_STATUS_CURRENT_REVISION[];
extern char STATEFUL_SET_STATUS_OBSERVED_GENERATION[];
extern char STATEFUL_SET_STATUS_READY_REPLICAS[];
extern char STATEFUL_SET_STATUS_REPLICAS[];
extern char STATEFUL_SET_STATUS_UPDATE_REVISION[];
extern char STATEFUL_SET_STATUS_UPDATE_REPLICAS[];

class stateful_set_status : public extensions::serializable<stateful_set_status> {
public:
    extensions::field<int, STATEFUL_SET_STATUS_COLLISION_COUNT> collision_count;
    extensions::field<
        extensions::special_list<stateful_set_condition>,
        STATEFUL_SET_STATUS_CONDITIONS> conditions;
    extensions::field<int, STATEFUL_SET_STATUS_CURRENT_REPLICAS> current_replicas;
    extensions::field<int, STATEFUL_SET_STATUS_CURRENT_REVISION> current_revision;
    extensions::field<int, STATEFUL_SET_STATUS_OBSERVED_GENERATION> observed_generation;
    extensions::field<int, STATEFUL_SET_STATUS_REPLICAS> replicas;
    extensions::field<int, STATEFUL_SET_STATUS_READY_REPLICAS> ready_replicas;
    extensions::field<int, STATEFUL_SET_STATUS_UPDATE_REPLICAS> update_replicas;
    extensions::field<int, STATEFUL_SET_STATUS_UPDATE_REVISION> update_revision;

    void bind(extensions::serializer_helper & helper);
};


}
}

#endif
