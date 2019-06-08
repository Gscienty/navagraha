#ifndef _NAVAGRAHA_KUBEENT_NODE_DAEMON_ENDPOINTS_H
#define _NAVAGRAHA_KUBEENT_NODE_DAEMON_ENDPOINTS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/daemon_endpoint.hpp"

namespace navagraha {
namespace kubeent {

extern char NODE_DAEMON_ENDPOINTS_KUBELET_ENDPOINT[];

class node_daemon_endpoints : public extensions::serializable<node_daemon_endpoints> {
public:
    extensions::field<
        daemon_endpoint,
        NODE_DAEMON_ENDPOINTS_KUBELET_ENDPOINT> kubelet_endpoint;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
