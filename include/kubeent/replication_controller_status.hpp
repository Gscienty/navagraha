#ifndef _NAVAGRAHA_KUBEENT_REPLICATION_CONTROLLER_STATUS_H
#define _NAVAGRAHA_KUBEENT_REPLICATION_CONTROLLER_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/replication_controller_condition.hpp"

namespace navagraha {
namespace kubeent {

extern char REPLICATION_CONTROLLER_STATUS_AVAILABLE_REPLICAS[];
extern char REPLICATION_CONTROLLER_STATUS_CONDITIONS[];
extern char REPLICATION_CONTROLLER_STATUS_FULLY_LABELED_REPLICAS[];
extern char REPLICATION_CONTROLLER_STATUS_OBSERVED_GENERATION[];
extern char REPLICATION_CONTROLLER_STATUS_READY_REPLICAS[];
extern char REPLICATION_CONTROLLER_STATUS_REPLICAS[];

class replication_controller_status : public serializable<replication_controller_status> {
public:
    extensions::field<int, REPLICATION_CONTROLLER_STATUS_AVAILABLE_REPLICAS> available_replicas;
    extensions::field<
        extensions::special_list<replication_controller_condition>,
        REPLICATION_CONTROLLER_STATUS_CONDITIONS> conditions;
    extensions::field<int, REPLICATION_CONTROLLER_STATUS_FULLY_LABELED_REPLICAS> fully_labeled_replicas;
    extensions::field<int, REPLICATION_CONTROLLER_STATUS_OBSERVED_GENERATION> observed_generation;
    extensions::field<int, REPLICATION_CONTROLLER_STATUS_READY_REPLICAS> ready_replicas;
    extensions::field<int, REPLICATION_CONTROLLER_STATUS_REPLICAS> replicas;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
