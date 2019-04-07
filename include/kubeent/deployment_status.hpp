#ifndef _NAVAGRAHA_KUBEENT_DEPLOYMENT_STATUS_H
#define _NAVAGRAHA_KUBEENT_DEPLOYMENT_STATUS_H

#include "extensions/field.hpp"
#include "extensions/list_wrapper.hpp"
#include "kubeent/deployment_condition.hpp"

namespace navagraha {
namespace kubeent {

extern char DEPLOYMENT_STATUS_AVAILABLE_REPLICAS[];
extern char DEPLOYMENT_STATUS_COLLISION_COUNT[];
extern char DEPLOYMENT_STATUS_CONDITIONS[];
extern char DEPLOYMENT_STATUS_OBSERVED_GENERATION[];
extern char DEPLOYMENT_STATUS_READY_REPLICAS[];
extern char DEPLOYMENT_STATUS_REPLICAS[];
extern char DEPLOYMENT_STATUS_UNAVAILABLE_REPLICAS[];
extern char DEPLOYMENT_STATUS_UPDATED_REPLICAS[];

class deployment_status {
public:
    extensions::field<int, DEPLOYMENT_STATUS_AVAILABLE_REPLICAS> available_replicas;
    extensions::field<int, DEPLOYMENT_STATUS_COLLISION_COUNT> collision_count;
    extensions::field<
        extensions::special_list<deployment_condition>,
        DEPLOYMENT_STATUS_CONDITIONS> conditions;
    extensions::field<int, DEPLOYMENT_STATUS_OBSERVED_GENERATION> observed_generation;
    extensions::field<int, DEPLOYMENT_STATUS_REPLICAS> replicas;
    extensions::field<int, DEPLOYMENT_STATUS_UNAVAILABLE_REPLICAS> unavailable_replicas;
    extensions::field<int, DEPLOYMENT_STATUS_UPDATED_REPLICAS> updated_replicas;

    static void serialize(deployment_status & obj, std::ostringstream & str);
};

}
}

#endif
