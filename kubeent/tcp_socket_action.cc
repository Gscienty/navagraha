#include "kubeent/tcp_socket_action.hpp"

namespace navagraha {
namespace kubeent {

char TCP_SOCKET_ACTION_HOST[] = "host";
char TCP_SOCKET_ACTION_PORT[] = "port";

void tcp_socket_action::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->host)
        .add(this->port);
}

}
}
