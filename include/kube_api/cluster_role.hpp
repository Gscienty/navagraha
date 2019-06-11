#ifndef _NAVAGRAHA_KUBE_API_CLUSTER_ROLE_H
#define _NAVAGRAHA_KUBE_API_CLUSTER_ROLE_H

#include "http_client/client.hpp"
#include "kubeent/cluster_role.hpp"
#include "kubeent/delete_options.hpp"
#include "kubeent/status.hpp"

namespace navagraha {
namespace kube_api {

class cluster_role : public http_client::client {
public:
    cluster_role(CURL * curl, const std::string host);

    kubeent::cluster_role create(kubeent::cluster_role & role);

    kubeent::status delete_(const std::string name,
                            kubeent::delete_options & opts);

    kubeent::status delete_collection();
};

}
}

#endif
