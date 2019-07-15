#ifndef _NAVAGRAHA_KUBE_API_POD_H
#define _NAVAGRAHA_KUBE_API_POD_H

#include "http_client/client.hpp"
#include "kubeent/pod.hpp"
#include <functional>

namespace navagraha {
namespace kube_api {

class pod : public http_client::client {
public:
    pod(CURL * curl, const std::string host);

    http_client::http_response create(const std::string namespace_, kubeent::pod pod_);

    http_client::http_response list(const std::string namespace_);
};

}
}

#endif
