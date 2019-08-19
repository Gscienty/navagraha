#ifndef _NAVAGRAHA_KUBE_API_HORIZONTAL_POD_AUTOSCALER_H
#define _NAVAGRAHA_KUBE_API_HORIZONTAL_POD_AUTOSCALER_H

#include "http_client/client.hpp"
#include "http_client/http_response.hpp"
#include "kubeent/horizontal_pod_autoscaler.hpp"
#include "kubeent/status.hpp"

namespace navagraha {
namespace kube_api {

class horizontal_pod_autoscaler : public http_client::client {
public:
    horizontal_pod_autoscaler(CURL * curl, const std::string host);

    http_client::http_response create(const std::string namespace_, kubeent::horizontal_pod_autoscaler & hpa);

    http_client::http_response delete_(const std::string namespace_, const std::string name);

    http_client::http_response read(const std::string namespace_, const std::string name);

    http_client::http_response list(const std::string namespace_);

    http_client::http_response replace(const std::string namespace_, const std::string name, kubeent::horizontal_pod_autoscaler & hpa);
}; 
}
}

#endif
