#include "kube_api/namespace.hpp"

namespace navagraha {
namespace kube_api {

namespace_::namespace_(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

http_client::http_response namespace_::read(const std::string name)
{
    return this->get_request("/api/v1/namespaces/" + name);
}

http_client::http_response namespace_::list()
{
    return this->get_request("/api/v1/namespaces");
}

http_client::http_response namespace_::create(kubeent::namespace_ & payload)
{
    this->set_payload(payload);
    return this->post_request("/api/v1/namespaces");
}

http_client::http_response namespace_::put(const std::string name, kubeent::namespace_ & payload)
{
    this->set_payload(payload);
    return this->post_request("/api/v1/namespaces/" + name);
}

http_client::http_response namespace_::delete_(const std::string name, kubeent::delete_options & opt)
{
    this->set_payload(opt);
    return this->delete_request("/api/v1/namespaces/" + name);
}

}
}
