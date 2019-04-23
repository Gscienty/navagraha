#include "kube_api/deployment.hpp"

namespace navagraha {
namespace kube_api {

deployment::deployment(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

kubeent::deployment deployment::create(const std::string namespace_,
                                       kubeent::deployment & deployment_)
{
    this->set_payload(deployment_);
    return this->post_call<kubeent::deployment>("/apis/apps/v1/namespaces/"
                                                + namespace_
                                                + "/deployments");
}

kubeent::deployment deployment::replace(const std::string namespace_,
                                        const std::string name,
                                        kubeent::deployment & deployment_)
{
    this->set_payload(deployment_);
    return this->put_call<kubeent::deployment>("/apis/apps/v1/namespaces/"
                                               + namespace_
                                               + "/deployments/"
                                               + name);
}

kubeent::status deployment::delete_(const std::string namespace_,
                                    const std::string name,
                                    kubeent::delete_options & options)
{
    this->set_payload(options);
    return this->delete_call<kubeent::status>("/apis/apps/v1/namespaces/"
                                              + namespace_
                                              + "/deployments/"
                                              + name);
}

kubeent::status deployment::delete_collection(const std::string namespace_)
{
    return this->delete_call<kubeent::status>("/apis/apps/v1/namespaces/"
                                              + namespace_
                                              + "/deployments");
}

kubeent::deployment deployment::read(const std::string namespace_,
                                     const std::string name)
{
    return this->get_call<kubeent::deployment>("/apis/apps/v1/namespaces/"
                                               + namespace_
                                               + "/deployments/"
                                               + name);
}

kubeent::deployment_list deployment::list(const std::string namespace_)
{
    return this->get_call<kubeent::deployment_list>("/apis/apps/v1/namespaces/"
                                                    + namespace_
                                                    + "/deployments");
}

kubeent::deployment_list deployment::list_all_namespace()
{
    return this->get_call<kubeent::deployment_list>("/apis/apps/v1/deployments");
}

}
}
