#include "kube_api/namespace.hpp"

#include <iostream>

namespace navagraha {
namespace kube_api {

namespace_::namespace_(CURL * curl, const std::string base_uri)
    : http_client::client(curl, base_uri)
{

}

kubeent::namespace_ namespace_::read(std::string name)
{
    return this->get_call<kubeent::namespace_>("/api/v1/namespaces/" + name);
}

kubeent::namespace_list namespace_::list()
{
    return this->get_call<kubeent::namespace_list>("/api/v1/namespaces");
}

}
}
