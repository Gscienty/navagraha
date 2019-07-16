#include "kube_api/deployment.hpp"

namespace navagraha {
namespace kube_api {

deployment::deployment(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

http_client::http_response deployment::create(const std::string namespace_,
                                       kubeent::deployment & deployment_)
{
    this->set_payload(deployment_);
    return this->post_request("/apis/apps/v1/namespaces/"
                              + namespace_
                              + "/deployments");
}

http_client::http_response deployment::replace(const std::string namespace_,
                                        const std::string name,
                                        kubeent::deployment & deployment_)
{
    this->set_payload(deployment_);
    return this->put_request("/apis/apps/v1/namespaces/"
                             + namespace_
                             + "/deployments/"
                             + name);
}

http_client::http_response deployment::delete_(const std::string namespace_,
                                    const std::string name,
                                    kubeent::delete_options & options)
{
    this->set_payload(options);
    return this->delete_request("/apis/apps/v1/namespaces/"
                                + namespace_
                                + "/deployments/"
                                + name);
}

http_client::http_response deployment::delete_collection(const std::string namespace_)
{
    return this->delete_request("/apis/apps/v1/namespaces/"
                                + namespace_
                                + "/deployments");
}

http_client::http_response deployment::read(const std::string namespace_,
                                     const std::string name)
{
    return this->get_request("/apis/apps/v1/namespaces/"
                             + namespace_
                             + "/deployments/"
                             + name);
}

http_client::http_response deployment::list(const std::string namespace_)
{
    return this->get_request("/apis/apps/v1/namespaces/"
                             + namespace_
                             + "/deployments");
}

http_client::http_response deployment::list_all_namespace()
{
    return this->get_request("/apis/apps/v1/deployments");
}

}
}
