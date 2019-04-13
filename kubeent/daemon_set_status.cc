#include "kubeent/daemon_set_status.hpp"

namespace navagraha {
namespace kubeent {

char DAEMON_SET_STATUS_COLLISION_COUNT[] = "collisionCount";
char DAEMON_SET_STATUS_CONDITIONS[] = "conditions";
char DAEMON_SET_STATUS_CURRENT_NUMBER_SCHEDULED[] = "currentNumberScheduled";
char DAEMON_SET_STATUS_DESIRED_NUMBER_SCHEDULED[] = "desiredNumberScheduled";
char DAEMON_SET_STATUS_NUMBER_AVAILABLE[] = "numberAvailable";
char DAEMON_SET_STATUS_NUMBER_MISSCHEDULED[] = "numberMisscheduled";
char DAEMON_SET_STATUS_NUMBER_READY[] = "numberReady";
char DAEMON_SET_STATUS_NUMBER_UNAVAILABLE[] = "numberUnavailable";
char DAEMON_SET_STATUS_OBSERVED_GENERATION[] = "observedGeneration";
char DAEMON_SET_STATUS_UPDATED_NUMBER_SCHEDULED[] = "updatedNumberScheduled";

void daemon_set_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->collision_count)
        .add(this->conditions)
        .add(this->current_number_scheduled)
        .add(this->desired_number_scheduled)
        .add(this->number_available)
        .add(this->number_misscheduled)
        .add(this->number_ready)
        .add(this->number_unavailable)
        .add(this->observed_generation)
        .add(this->updated_number_scheduled);
}

}
}
