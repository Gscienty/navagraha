#include "kube_api/cluster_role_binding.hpp"

namespace navagraha {
namespace kube_api {
cluster_role_binding::cluster_role_binding(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

kubeent::cluster_role_binding cluster_role_binding::create(kubeent::cluster_role_binding & binding)
{
    this->set_payload(binding);

    return this->post_call<kubeent::cluster_role_binding>("/apis/rbac.authorization.k8s.io/v1/clusterrolebindings");
}

kubeent::status cluster_role_binding::delete_(const std::string name,
                                              kubeent::delete_options & opts)
{
    this->set_payload(opts);

    return this->delete_call<kubeent::status>("/api/rbac.authorization.k8s.io/v1/clusterrolebindings/"
                                              + name);
}

kubeent::status cluster_role_binding::delete_collection()
{
    return this->delete_call<kubeent::status>("/api/rbac.authorization.k8s.io/v1/clusterrolebindings");
}

}
}
