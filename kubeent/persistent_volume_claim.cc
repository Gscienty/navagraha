#include "kubeent/persistent_volume_claim.hpp"

namespace navagraha {
namespace kubeent {

char PERSISTENT_VOLUME_CLAIM_API_VERSION[] = "apiVersion";
char PERSISTENT_VOLUME_CLAIM_KIND[] = "kind";
char PERSISTENT_VOLUME_CLAIM_METADATA[] = "metadata";
char PERSISTENT_VOLUME_CLAIM_SPEC[] = "spec";
char PERSISTENT_VOLUME_CLAIM_STATUS[] = "status";

void persistent_volume_claim::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->kind)
        .add(this->metadata)
        .add(this->spec)
        .add(this->status);
}

}
}
