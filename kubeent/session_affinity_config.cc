#include "kubeent/session_affinity_config.hpp"

namespace navagraha {
namespace kubeent {

char SESSION_AFFINITY_CONFIG_CLIENT_IP[] = "clientIP";

void session_affinity_config::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->client_ip);
}

}
}
