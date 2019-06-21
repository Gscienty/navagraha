#include "kube_api/node.hpp"

namespace navagraha {
namespace kube_api {


node::node(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

kubeent::node node::read(const std::string name)
{
    return this->get_request("/api/v1/nodes/" + name)
        .get<kubeent::node>();
}

}
}
