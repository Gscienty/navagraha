#include "kube_api/pod.hpp"

namespace navagraha {
namespace kube_api {

pod::pod(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

http_client::http_response pod::create(const std::string namespace_, kubeent::pod pod_)
{
    this->set_payload(pod_);

    return this->post_request("/api/v1/namespaces/"
                              + namespace_
                              + "/pods");
}

http_client::http_response pod::list(const std::string namespace_)
{
    return this->get_request("/api/v1/namespaces/"
                             + namespace_
                             + "/pods");
}

}
}
