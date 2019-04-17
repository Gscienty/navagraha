#include "kubeent/daemon_endpoint.hpp"

namespace navagraha {
namespace kubeent {

char DAEMON_ENDPOINT_PORT[] = "port";

void daemon_endpoint::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->port);
}

}
}
