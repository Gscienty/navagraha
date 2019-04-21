#include "kube_api/namespace.hpp"

namespace navagraha {
namespace kube_api {

namespace_::namespace_(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

kubeent::namespace_ namespace_::read(const std::string name)
{
    return this->get_call<kubeent::namespace_>("/api/v1/namespaces/" + name);
}

kubeent::namespace_list namespace_::list()
{
    return this->get_call<kubeent::namespace_list>("/api/v1/namespaces");
}

kubeent::namespace_ namespace_::create(kubeent::namespace_ & payload)
{
    this->set_payload(payload);
    return this->post_call<kubeent::namespace_>("/api/v1/namespaces");
}

kubeent::namespace_ namespace_::put(const std::string name, kubeent::namespace_ & payload)
{
    this->set_payload(payload);
    return this->post_call<kubeent::namespace_>("/api/v1/namespaces/" + name);
}

}
}
