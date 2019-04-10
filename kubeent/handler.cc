#include "kubeent/handler.hpp"

namespace navagraha {
namespace kubeent {

char HANDLER_EXEC[] = "exec";
char HANDLER_HTTP_GET[] = "httpGet";
char HANDLER_TCP_SOCKET[] = "tcpSocket";

void handler::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->exec)
        .add(this->http_get)
        .add(this->tcp_socket);
}

}
}
