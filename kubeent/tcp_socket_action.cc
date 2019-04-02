#include "kubeent/tcp_socket_action.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char TCP_SOCKET_ACTION_HOST[] = "host";
char TCP_SOCKET_ACTION_PORT[] = "port";

void tcp_socket_action::serialize(tcp_socket_action & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.host)
        .add(obj.port)
        .serialize(str);
}

}
}
