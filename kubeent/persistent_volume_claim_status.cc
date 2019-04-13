#include "kubeent/persistent_volume_claim_status.hpp"

namespace navagraha {
namespace kubeent {

char PERSISTENT_VOLUME_CLAIM_STATUS_ACCESS_MODES[] = "accessModes";
char PERSISTENT_VOLUME_CLAIM_STATUS_CAPACITY[] = "capacity";
char PERSISTENT_VOLUME_CLAIM_CONDITIONS[] = "conditions";
char PERSISTENT_VOLUME_CLAIM_PHASE[] = "phase";

void persistent_volume_claim_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->access_modes)
        .add(this->capacity)
        .add(this->conditions)
        .add(this->phase);
}

}
}
