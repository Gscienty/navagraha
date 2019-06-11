#ifndef _NAVAGRAHA_KUBE_API_CLUSTER_ROLE_BINDING_H
#define _NAVAGRAHA_KUBE_API_CLUSTER_ROLE_BINDING_H

#include "http_client/client.hpp"
#include "kubeent/cluster_role_binding.hpp"
#include "kubeent/delete_options.hpp"
#include "kubeent/status.hpp"

namespace navagraha {
namespace kube_api {

class cluster_role_binding : public http_client::client {
public:
    cluster_role_binding(CURL * curl, const std::string host);

    kubeent::cluster_role_binding create(kubeent::cluster_role_binding & binding);

    kubeent::status delete_(const std::string name,
                            kubeent::delete_options & opts);

    kubeent::status delete_collection();
};

}
}

#endif
