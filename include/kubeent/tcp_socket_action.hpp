#ifndef _NAVAGRAHA_KUBEENT_TCP_SOCKET_ACTION_H
#define _NAVAGRAHA_KUBEENT_TCP_SOCKET_ACTION_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char TCP_SOCKET_ACTION_HOST[];
extern char TCP_SOCKET_ACTION_PORT[];

class tcp_socket_action : public serializable<tcp_socket_action> {
public:
    extensions::field<std::string, TCP_SOCKET_ACTION_HOST> host;
    extensions::field<int, TCP_SOCKET_ACTION_PORT> port;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
