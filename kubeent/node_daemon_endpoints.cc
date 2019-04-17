#include "kubeent/node_daemon_endpoints.hpp"

namespace navagraha {
namespace kubeent {

char NODE_DAEMON_ENDPOINTS_KUBELET_ENDPOINT[] = "kubeletEndpoint";

void node_daemon_endpoints::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->kubelet_endpoint);
}

}
}

