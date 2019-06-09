#include "kube_api/config_map.hpp"

namespace navagraha {
namespace kube_api {

config_map::config_map(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

kubeent::config_map config_map::create(const std::string namespace_,
                                       kubeent::config_map & config_map_)
{
    this->set_payload(config_map_);

    return this->post_call<kubeent::config_map>("/api/v1/namespaces/"
                                                + namespace_
                                                + "/configmaps");
}

kubeent::status config_map::delete_(const std::string namespace_,
                                    const std::string name,
                                    kubeent::delete_options & opts)
{
    this->set_payload(opts);

    return this->delete_call<kubeent::status>("/api/v1/namespaces/"
                                              + namespace_
                                              + "/configmaps/"
                                              + name);
}

}
}
