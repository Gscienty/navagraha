#include "kube_api/daemon_set.hpp"

namespace navagraha {
namespace kube_api {

daemon_set::daemon_set(CURL * curl, const std::string uri)
    : http_client::client(curl, uri)
{

}

kubeent::daemon_set daemon_set::create(const std::string namespace_,
                                       kubeent::daemon_set & daemon_set_)
{
    this->set_payload(daemon_set_);
    return this->post_request("/apis/apps/v1/namespaces/"
                              + namespace_
                              + "/daemonsets")
        .get<kubeent::daemon_set>();
}

kubeent::daemon_set daemon_set::replace(const std::string namespace_,
                                        const std::string name,
                                        kubeent::daemon_set & daemon_set_)
{
    this->set_payload(daemon_set_);
    return this->put_request("/apis/apps/v1/namespaces/"
                             + namespace_
                             + "/daemonsets/"
                             + name)
        .get<kubeent::daemon_set>();
}

kubeent::status daemon_set::delete_(const std::string namespace_,
                                    const std::string name,
                                    kubeent::delete_options & options)
{
    this->set_payload(options);
    return this->delete_request("/apis/apps/v1/namespaces/"
                                + namespace_
                                + "/daemonsets/"
                                + name)
        .get<kubeent::status>();
}

kubeent::status daemon_set::delete_collection(const std::string namespace_)
{
    return this->delete_request("/apis/apps/v1/namespaces/"
                                + namespace_
                                + "/daemonsets")
        .get<kubeent::status>();
}

kubeent::daemon_set daemon_set::read(const std::string namespace_,
                                     const std::string name)
{
    return this->get_request("/apis/apps/v1/namespaces/"
                             + namespace_
                             + "/daemonsets/"
                             + name)
        .get<kubeent::daemon_set>();
}

kubeent::daemon_set_list daemon_set::list(const std::string namespace_)
{
    return this->get_request("/apis/apps/v1/namespaces/"
                             + namespace_
                             + "/daemonsets")
        .get<kubeent::daemon_set_list>();
}

kubeent::daemon_set_list daemon_set::list_all_namespace()
{
    return this->get_request("/apis/apps/v1/daemonsets")
        .get<kubeent::daemon_set_list>();
}


}
}
