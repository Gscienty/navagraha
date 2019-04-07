#include "kubeent/handler.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char HANDLER_EXEC[] = "exec";
char HANDLER_HTTP_GET[] = "httpGet";
char HANDLER_TCP_SOCKET[] = "tcpSocket";

void handler::serialize(handler & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.exec)
        .add(obj.http_get)
        .add(obj.tcp_socket)
        .serialize(str);
}

}
}
