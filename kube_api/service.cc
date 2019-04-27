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
    return this->post_call<kubeent::service>("/api/v1/namesapces/"
                                             + namespace_
                                             + "/services");
}


kubeent::service service::replace(const std::string namespace_,
                                  const std::string name,
                                  kubeent::service & service_)
{
    this->set_payload(service_);
    return this->post_call<kubeent::service>("/api/v1/namespaces/"
                                             + namespace_
                                             + "/services/"
                                             + name);
}

kubeent::status service::delete_(const std::string namespace_,
                                 const std::string name,
                                 kubeent::delete_options & opt)
{
    this->set_payload(opt);
    return this->delete_call<kubeent::status>("/api/v1/namesapces/"
                                               + namespace_
                                               + "/services/"
                                               + name);
}

kubeent::service service::read(const std::string namespace_,
                               const std::string name)
{
    return this->get_call<kubeent::service>("/api/v1/namespaces/"
                                            + namespace_
                                            + "/services/"
                                            + name);
}

kubeent::service_list service::list(const std::string namespace_)
{
    return this->get_call<kubeent::service_list>("/api/v1/namespaces/"
                                                 + namespace_
                                                 + "/services");
}

kubeent::service_list service::list_all_namespace()
{
    return this->get_call<kubeent::service_list>("/api/v1/services");
}

}
}
