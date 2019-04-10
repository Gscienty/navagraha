#ifndef _NAVAGRAHA_KUBEENT_HTTP_GET_ACTION_H
#define _NAVAGRAHA_KUBEENT_HTTP_GET_ACTION_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/http_header.hpp"

namespace navagraha {
namespace kubeent {

extern char HTTP_GET_ACTION_HOST[];
extern char HTTP_GET_ACTION_HTTP_HEADERS[];
extern char HTTP_GET_ACTION_PATH[];
extern char HTTP_GET_ACTION_PORT[];
extern char HTTP_GET_ACTION_SCHEME[];

class http_get_action : public serializable<http_get_action> {
public:
    extensions::field<std::string, HTTP_GET_ACTION_HOST> host;
    extensions::field<
        extensions::special_list<http_header>,
        HTTP_GET_ACTION_HTTP_HEADERS> http_headers;
    extensions::field<std::string, HTTP_GET_ACTION_PATH> path;
    extensions::field<int, HTTP_GET_ACTION_PORT> port;
    extensions::field<std::string, HTTP_GET_ACTION_SCHEME> scheme;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
