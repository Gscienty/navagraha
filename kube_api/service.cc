#include "kube_api/service.hpp"

namespace navagraha {
namespace kube_api {

service::service(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

http_client::http_response service::create(const std::string namespace_,
                                 kubeent::service & service_)
{
    this->set_payload(service_);
    return this->post_request("/api/v1/namespaces/"
                              + namespace_
                              + "/services");
}


http_client::http_response service::replace(const std::string namespace_,
                                  const std::string name,
                                  kubeent::service & service_)
{
    this->set_payload(service_);
    return this->post_request("/api/v1/namespaces/"
                              + namespace_
                              + "/services/"
                              + name);
}

http_client::http_response service::delete_(const std::string namespace_,
                                 const std::string name,
                                 kubeent::delete_options & opt)
{
    this->set_payload(opt);
    return this->delete_request("/api/v1/namespaces/"
                                + namespace_
                                + "/services/"
                                + name);
}

http_client::http_response service::read(const std::string namespace_,
                               const std::string name)
{
    return this->get_request("/api/v1/namespaces/"
                             + namespace_
                             + "/services/"
                             + name);
}

http_client::http_response service::list(const std::string namespace_)
{
    return this->get_request("/api/v1/namespaces/"
                             + namespace_
                             + "/services");
}

http_client::http_response service::list_all_namespace()
{
    return this->get_request("/api/v1/services");
}

}
}
