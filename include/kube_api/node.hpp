#ifndef _NAVAGRAHA_KUBE_API_NODE_H
#define _NAVAGRAHA_KUBE_API_NODE_H

#include "http_client/client.hpp"
#include "kubeent/node.hpp"

namespace navagraha {
namespace kube_api {

class node : public http_client::client {
public:
    node(CURL * curl, const std::string host);

    kubeent::node read(const std::string name);
};

}
}

#endif
