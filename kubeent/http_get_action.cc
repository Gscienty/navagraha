#include "kubeent/http_get_action.hpp"

namespace navagraha {
namespace kubeent {

char HTTP_GET_ACTION_HOST[] = "host";
char HTTP_GET_ACTION_HTTP_HEADERS[] = "httpHeaders";
char HTTP_GET_ACTION_PATH[] = "path";
char HTTP_GET_ACTION_PORT[] = "port";
char HTTP_GET_ACTION_SCHEME[] = "scheme";

void http_get_action::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->host)
        .add(this->http_headers)
        .add(this->path)
        .add(this->path)
        .add(this->scheme);
}

}
}
