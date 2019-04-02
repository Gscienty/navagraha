#include "kubeent/http_get_action.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char HTTP_GET_ACTION_HOST[] = "host";
char HTTP_GET_ACTION_HTTP_HEADERS[] = "httpHeaders";
char HTTP_GET_ACTION_PATH[] = "path";
char HTTP_GET_ACTION_PORT[] = "port";
char HTTP_GET_ACTION_SCHEME[] = "scheme";

void http_get_action::serialize(http_get_action & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.host)
        .add(obj.http_headers)
        .add(obj.path)
        .add(obj.port)
        .add(obj.scheme)
        .serialize(str);
}

}
}
