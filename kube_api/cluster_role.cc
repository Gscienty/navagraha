#include "kube_api/cluster_role.hpp"

namespace navagraha {
namespace kube_api {

cluster_role::cluster_role(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}


kubeent::cluster_role cluster_role::create(kubeent::cluster_role & role)
{
    this->set_payload(role);

    return this->post_call<kubeent::cluster_role>("/apis/rbac.authorization.k8s.io/v1/clusterroles");
}

kubeent::status cluster_role::delete_(const std::string name,
                                      kubeent::delete_options & opts)
{
    this->set_payload(opts);

    return this->delete_call<kubeent::status>("/apis/rbac.authorization.k8s.io/v1/clusterroles/"
                                               + name);
}

kubeent::status cluster_role::delete_collection()
{
    return this->delete_call<kubeent::status>("/apis/rbac.authorization.k8s.io/v1/clusterroles");
}

}
}
