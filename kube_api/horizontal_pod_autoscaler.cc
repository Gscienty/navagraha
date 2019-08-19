#include "kube_api/horizontal_pod_autoscaler.hpp"

namespace navagraha {
namespace kube_api {


horizontal_pod_autoscaler::horizontal_pod_autoscaler(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

http_client::http_response horizontal_pod_autoscaler::create(const std::string namespace_, kubeent::horizontal_pod_autoscaler & hpa)
{
    this->set_payload(hpa);

    return this->post_request("/apis/autoscaling/v1/namespaces/"
                              + namespace_
                              + "/horizontalpodautoscalers");
}

http_client::http_response horizontal_pod_autoscaler::delete_(const std::string namespace_, const std::string name)
{
    return this->delete_request("/apis/autoscaling/v1/namespaces/"
                                + namespace_
                                + "/horizontalpodautoscalers/"
                                + name);
}

http_client::http_response horizontal_pod_autoscaler::read(const std::string namespace_, const std::string name)
{
    return this->get_request("/apis/autoscaling/v1/namespaces/"
                             + namespace_
                             + "/horizontalpodautoscalers/"
                             + name);
}

http_client::http_response horizontal_pod_autoscaler::list(const std::string namespace_)
{
    return this->get_request("/apis/autoscaling/v1/namespaces/"
                             + namespace_
                             + "/horizontalpodautoscalers");
}

http_client::http_response horizontal_pod_autoscaler::replace(const std::string namespace_,
                                                              const std::string name,
                                                              kubeent::horizontal_pod_autoscaler & hpa)
{
    this->set_payload(hpa);

    return this->put_request("/apis/autoscaling/v1/namespaces/"
                             + namespace_
                             + "/horizontalpodautoscalers/"
                             + name);
}

}
}
