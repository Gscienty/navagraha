#include "kube_api/service.hpp"

namespace navagraha {
namespace kube_api {

service::service(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

kubeent::service service::create(const std::string namespace_,
                                 kubeent::service & service_)
{
    this->set_payload(service_);
    return this->post_request("/api/v1/namespaces/"
                              + namespace_
                              + "/services")
        .get<kubeent::service>();
}


kubeent::service service::replace(const std::string namespace_,
                                  const std::string name,
                                  kubeent::service & service_)
{
    this->set_payload(service_);
    return this->post_request("/api/v1/namespaces/"
                              + namespace_
                              + "/services/"
                              + name)
        .get<kubeent::service>();
}

kubeent::status service::delete_(const std::string namespace_,
                                 const std::string name,
                                 kubeent::delete_options & opt)
{
    this->set_payload(opt);
    return this->delete_request("/api/v1/namespaces/"
                                + namespace_
                                + "/services/"
                                + name)
        .get<kubeent::status>();
}

kubeent::service service::read(const std::string namespace_,
                               const std::string name)
{
    return this->get_request("/api/v1/namespaces/"
                             + namespace_
                             + "/services/"
                             + name)
        .get<kubeent::service>();
}

kubeent::service_list service::list(const std::string namespace_)
{
    return this->get_request("/api/v1/namespaces/"
                             + namespace_
                             + "/services")
        .get<kubeent::service_list>();
}

kubeent::service_list service::list_all_namespace()
{
    return this->get_request("/api/v1/services")
        .get<kubeent::service_list>();
}

}
}
