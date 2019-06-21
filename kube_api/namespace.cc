#include "kube_api/namespace.hpp"

namespace navagraha {
namespace kube_api {

namespace_::namespace_(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

kubeent::namespace_ namespace_::read(const std::string name)
{
    return this->get_request("/api/v1/namespaces/" + name)
        .get<kubeent::namespace_>();
}

kubeent::namespace_list namespace_::list()
{
    return this->get_request("/api/v1/namespaces")
        .get<kubeent::namespace_list>();
}

kubeent::namespace_ namespace_::create(kubeent::namespace_ & payload)
{
    this->set_payload(payload);
    return this->post_request("/api/v1/namespaces")
        .get<kubeent::namespace_>();
}

kubeent::namespace_ namespace_::put(const std::string name, kubeent::namespace_ & payload)
{
    this->set_payload(payload);
    return this->post_request("/api/v1/namespaces/" + name)
        .get<kubeent::namespace_>();
}

kubeent::status namespace_::delete_(const std::string name, kubeent::delete_options & opt)
{
    this->set_payload(opt);
    return this->delete_request("/api/v1/namespaces/" + name)
        .get<kubeent::status>();
}

}
}
