#ifndef _NAVAGRAHA_KUBE_API_SERVICE_H
#define _NAVAGRAHA_KUBE_API_SERVICE_H

#include "http_client/client.hpp"
#include "kubeent/service.hpp"
#include "kubeent/service_list.hpp"
#include "kubeent/delete_options.hpp"
#include "kubeent/status.hpp"

namespace navagraha {
namespace kube_api {

class service : public http_client::client {
public:
    service(CURL * curl, const std::string host);

    kubeent::service create(const std::string namespace_,
                            kubeent::service & service_);

    kubeent::service replace(const std::string namespace_,
                             const std::string name,
                             kubeent::service & service_);

    kubeent::status delete_(const std::string namespace_,
                            const std::string name,
                            kubeent::delete_options & opt);

    kubeent::service read(const std::string namespace_,
                          const std::string name);

    kubeent::service_list list(const std::string namespace_);

    kubeent::service_list list_all_namespace();
};

}
}

#endif
