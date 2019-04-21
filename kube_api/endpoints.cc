#include "kube_api/endpoints.hpp"

namespace navagraha {
namespace kube_api {


kubeent::endpoints endpoints::create(const std::string namespace_,
                                     kubeent::endpoints & endpoints_)
{
    this->set_payload(endpoints_);
    return this->post_call<kubeent::endpoints>("/api/v1/namespaces/"
                                               + namespace_
                                               + "/endpoints");
}

kubeent::endpoints endpoints::replace(const std::string namespace_,
                                      const std::string name,
                                      kubeent::endpoints & endpoints_)
{
    this->set_payload(endpoints_);
    return this->put_call<kubeent::endpoints>("/api/v1/namespaces/"
                                              + namespace_
                                              + "/endpoints/"
                                              + name);
}
kubeent::status endpoints::delete_(const std::string namespace_,
                                   const std::string name,
                                   kubeent::delete_options & option)
{
    this->set_payload(option);
    return this->delete_call<kubeent::status>("/api/v1/namespaces/"
                                              + namespace_
                                              + "/endpoints/"
                                              + name);
}

kubeent::status endpoints::delete_collection(const std::string namespace_)
{
    return this->delete_call<kubeent::status>("/api/v1/namespaces/"
                                              + namespace_
                                              + "/endpoints");
}

kubeent::endpoints endpoints::read(const std::string namespace_,
                                   const std::string name)
{
    return this->get_call<kubeent::endpoints>("/api/v1/namespaces/"
                                              + namespace_
                                              + "/endpoints/"
                                              + name);
}

kubeent::endpoints_list endpoints::list(const std::string namespace_)
{
    return this->get_call<kubeent::endpoints_list>("/api/v1/namespaces/"
                                                   + namespace_
                                                   + "/endpoints");
}

kubeent::endpoints_list endpoints::list_all_namespace()
{
    return this->get_call<kubeent::endpoints_list>("/api/v1/endpoints");
}

}
}
