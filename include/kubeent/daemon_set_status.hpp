#ifndef _NAVAGRAHA_KUBEENT_DAEMON_SET_STATUS_H
#define _NAVAGRAHA_KUBEENT_DAEMON_SET_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/daemon_set_condition.hpp"

namespace navagraha {
namespace kubeent {

extern char DAEMON_SET_STATUS_COLLISION_COUNT[];
extern char DAEMON_SET_STATUS_CONDITIONS[];
extern char DAEMON_SET_STATUS_CURRENT_NUMBER_SCHEDULED[];
extern char DAEMON_SET_STATUS_DESIRED_NUMBER_SCHEDULED[];
extern char DAEMON_SET_STATUS_NUMBER_AVAILABLE[];
extern char DAEMON_SET_STATUS_NUMBER_MISSCHEDULED[];
extern char DAEMON_SET_STATUS_NUMBER_READY[];
extern char DAEMON_SET_STATUS_NUMBER_UNAVAILABLE[];
extern char DAEMON_SET_STATUS_OBSERVED_GENERATION[];
extern char DAEMON_SET_STATUS_UPDATED_NUMBER_SCHEDULED[];

class daemon_set_status : public extensions::serializable<daemon_set_status> {
public:
    extensions::field<int, DAEMON_SET_STATUS_COLLISION_COUNT> collision_count;
    extensions::field<
        extensions::special_list<daemon_set_condition>,
        DAEMON_SET_STATUS_CONDITIONS> conditions;
    extensions::field<int, DAEMON_SET_STATUS_CURRENT_NUMBER_SCHEDULED> current_number_scheduled;
    extensions::field<int, DAEMON_SET_STATUS_DESIRED_NUMBER_SCHEDULED> desired_number_scheduled;
    extensions::field<int, DAEMON_SET_STATUS_NUMBER_AVAILABLE> number_available;
    extensions::field<int, DAEMON_SET_STATUS_NUMBER_MISSCHEDULED> number_misscheduled;
    extensions::field<int, DAEMON_SET_STATUS_NUMBER_READY> number_ready;
    extensions::field<int, DAEMON_SET_STATUS_NUMBER_UNAVAILABLE> number_unavailable;
    extensions::field<int, DAEMON_SET_STATUS_OBSERVED_GENERATION> observed_generation;
    extensions::field<int, DAEMON_SET_STATUS_UPDATED_NUMBER_SCHEDULED> updated_number_scheduled;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
