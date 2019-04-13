#include "kubeent/client_ip_config.hpp"

namespace navagraha {
namespace kubeent {

char CLIENT_IP_CONFIG_TIMEOUT_SECONDS[] = "timeoutSeconds";

void client_ip_config::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->timeout_seconds);
}

}
}
