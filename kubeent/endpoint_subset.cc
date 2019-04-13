#include "kubeent/endpoint_subset.hpp"

namespace navagraha {
namespace kubeent {

char ENDPOINT_SUBSET_ADDRESSES[] = "addresses";
char ENDPOINT_SUBSET_NOT_READY_ADDRESSES[] = "notReadyAddresses";
char ENDPOINT_SUBSET_PORTS[] = "ports";

void endpoint_subset::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->addresses)
        .add(this->not_ready_addresses)
        .add(this->ports);
}

}
}
