#ifndef _NAVAGRAHA_KUBEENT_KUBEENT_HANDLER_H
#define _NAVAGRAHA_KUBEENT_KUBEENT_HANDLER_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/exec_action.hpp"
#include "kubeent/http_get_action.hpp"
#include "kubeent/tcp_socket_action.hpp"

namespace navagraha {
namespace kubeent {

extern char HANDLER_EXEC[];
extern char HANDLER_HTTP_GET[];
extern char HANDLER_TCP_SOCKET[];

class handler : public serializable<handler> {
public:
    extensions::field<exec_action, HANDLER_EXEC> exec;
    extensions::field<http_get_action, HANDLER_HTTP_GET> http_get;
    extensions::field<tcp_socket_action, HANDLER_TCP_SOCKET> tcp_socket;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
