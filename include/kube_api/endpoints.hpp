#ifndef _NAVAGRAHA_KUBE_API_END_POINTS_H
#define _NAVAGRAHA_KUBE_API_END_POINTS_H

#include "http_client/client.hpp"
#include "kubeent/endpoints.hpp"
#include "kubeent/endpoints_list.hpp"
#include "kubeent/delete_options.hpp"
#include "kubeent/status.hpp"

namespace navagraha {
namespace kube_api {

class endpoints : public http_client::client {
public:
    endpoints(CURL * curl, const std::string uri);

    kubeent::endpoints create(const std::string namespace_,
                              kubeent::endpoints & endpoints_);

    kubeent::endpoints replace(const std::string namespace_,
                               const std::string name,
                               kubeent::endpoints & endpoints_);

    kubeent::status delete_(const std::string namespace_,
                            const std::string name,
                            kubeent::delete_options & option);

    kubeent::status delete_collection(const std::string namespace_);

    kubeent::endpoints read(const std::string namespace_,
                            const std::string name);

    kubeent::endpoints_list list(const std::string namespace_);

    kubeent::endpoints_list list_all_namespace();
};

}
}

#endif
