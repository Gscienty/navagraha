#ifndef _NAVAGRAHA_KUBEENT_REPLICA_SET_STATUS_H
#define _NAVAGRAHA_KUBEENT_REPLICA_SET_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/replica_set_condition.hpp"

namespace navagraha {
namespace kubeent {

extern char REPLICA_SET_STATUS_AVAILABLE_REPLICAS[];
extern char REPLICA_SET_STATUS_CONDITIONS[];
extern char REPLICA_SET_STATUS_FULLY_LABELED_REPLICAS[];
extern char REPLICA_SET_STATUS_OBSERVED_GENERATION[];
extern char REPLICA_SET_STATUS_READY_REPLICAS[];
extern char REPLICA_SET_STATUS_REPLICAS[];

class replica_set_status : public extensions::serializable<replica_set_status> {
public:
    extensions::field<int, REPLICA_SET_STATUS_AVAILABLE_REPLICAS> available_replicas;
    extensions::field<
        extensions::special_list<replica_set_condition>,
        REPLICA_SET_STATUS_CONDITIONS> conditions;
    extensions::field<int, REPLICA_SET_STATUS_FULLY_LABELED_REPLICAS> fully_labeled_replicas;
    extensions::field<int, REPLICA_SET_STATUS_OBSERVED_GENERATION> observed_generation;
    extensions::field<int, REPLICA_SET_STATUS_READY_REPLICAS> ready_replicas;
    extensions::field<int, REPLICA_SET_STATUS_REPLICAS> replicas;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
