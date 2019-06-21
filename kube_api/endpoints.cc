#include "kube_api/endpoints.hpp"

namespace navagraha {
namespace kube_api {


kubeent::endpoints endpoints::create(const std::string namespace_,
                                     kubeent::endpoints & endpoints_)
{
    this->set_payload(endpoints_);
    return this->post_request("/api/v1/namespaces/"
                              + namespace_
                              + "/endpoints")
        .get<kubeent::endpoints>();
}

kubeent::endpoints endpoints::replace(const std::string namespace_,
                                      const std::string name,
                                      kubeent::endpoints & endpoints_)
{
    this->set_payload(endpoints_);
    return this->put_request("/api/v1/namespaces/"
                             + namespace_
                             + "/endpoints/"
                             + name)
        .get<kubeent::endpoints>();
}
kubeent::status endpoints::delete_(const std::string namespace_,
                                   const std::string name,
                                   kubeent::delete_options & option)
{
    this->set_payload(option);
    return this->delete_request("/api/v1/namespaces/"
                                + namespace_
                                + "/endpoints/"
                                + name)
        .get<kubeent::status>();
}

kubeent::status endpoints::delete_collection(const std::string namespace_)
{
    return this->delete_request("/api/v1/namespaces/"
                                + namespace_
                                + "/endpoints")
        .get<kubeent::status>();
}

kubeent::endpoints endpoints::read(const std::string namespace_,
                                   const std::string name)
{
    return this->get_request("/api/v1/namespaces/"
                             + namespace_
                             + "/endpoints/"
                             + name)
        .get<kubeent::endpoints>();
}

kubeent::endpoints_list endpoints::list(const std::string namespace_)
{
    return this->get_request("/api/v1/namespaces/"
                             + namespace_
                             + "/endpoints")
        .get<kubeent::endpoints_list>();
}

kubeent::endpoints_list endpoints::list_all_namespace()
{
    return this->get_request("/api/v1/endpoints")
        .get<kubeent::endpoints_list>();
}

}
}
