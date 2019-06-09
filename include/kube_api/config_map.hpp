#ifndef _NAVAGRAHA_KUBE_API_CONFIG_MAP_H
#define _NAVAGRAHA_KUBE_API_CONFIG_MAP_H

#include "http_client/client.hpp"
#include "kubeent/config_map.hpp"
#include "kubeent/status.hpp"
#include "kubeent/delete_options.hpp"

namespace navagraha {
namespace kube_api {

class config_map : public http_client::client {
public:
    config_map(CURL * curl, const std::string host);

    kubeent::config_map create(const std::string namespace_,
                               kubeent::config_map & config_map_);

    kubeent::status delete_(const std::string namespace_,
                            const std::string name,
                            kubeent::delete_options & opts);
};

}
}

#endif
