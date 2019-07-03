#ifndef _NAVAGRAHA_KUBE_API_POD_H
#define _NAVAGRAHA_KUBE_API_POD_H

#include "http_client/client.hpp"
#include "kubeent/pod.hpp"

namespace navagraha {
namespace kube_api {

class pod : public http_client::client {
public:
    pod(CURL * curl, const std::string host);

    kubeent::pod create(const std::string namespace_, kubeent::pod pod_);
};

}
}

#endif
