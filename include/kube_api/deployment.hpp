#ifndef _NAVAGRAHA_KUBE_API_DEPLOYMENT_H
#define _NAVAGRAHA_KUBE_API_DEPLOYMENT_H

#include "http_client/client.hpp"
#include "kubeent/deployment.hpp"
#include "kubeent/status.hpp"
#include "kubeent/delete_options.hpp"
#include "kubeent/deployment_list.hpp"

namespace navagraha {
namespace kube_api {

class deployment : public http_client::client {
public:
    deployment(CURL * curl, const std::string host);

    kubeent::deployment create(const std::string namespace_,
                               kubeent::deployment & deployment_);

    kubeent::deployment replace(const std::string namespace_,
                                const std::string name,
                                kubeent::deployment & deployment_);

    kubeent::status delete_(const std::string namespace_,
                            const std::string name,
                            kubeent::delete_options & options);

    kubeent::status delete_collection(const std::string namespace_);

    kubeent::deployment read(const std::string namespace_,
                             const std::string name);

    kubeent::deployment_list list(const std::string namespace_);

    kubeent::deployment_list list_all_namespace();
};

}
}

#endif
