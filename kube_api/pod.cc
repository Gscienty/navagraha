#include "kube_api/pod.hpp"

namespace navagraha {
namespace kube_api {

pod::pod(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

kubeent::pod pod::create(const std::string namespace_, kubeent::pod pod_)
{
    this->set_payload(pod_);

    return this->post_request("/api/v1/namespaces/"
                              + namespace_
                              + "/pods")
        .get<kubeent::pod>();
}

}
}
