#include "kube_api/secret.hpp"

namespace navagraha {
namespace kube_api {

secret::secret(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

kubeent::secret secret::create(const std::string namespace_,
                               kubeent::secret & secret)
{
    this->set_payload(secret);
    return this->post_request("/api/v1/namespaces/"
                              + namespace_
                              + "/secrets")
        .get<kubeent::secret>();
}

kubeent::status secret::delete_(const std::string namespace_,
                                const std::string name,
                                kubeent::delete_options & opts)
{
    this->set_payload(opts);
    return this->delete_request("/api/v1/namespaces/"
                                + namespace_
                                + "/secrets/"
                                + name)
        .get<kubeent::status>();
}

kubeent::status secret::delete_collecton(const std::string namespace_,
                                         kubeent::delete_options & opts)
{
    this->set_payload(opts);
    return this->delete_request("/api/v1/namespaces/"
                                + namespace_
                                + "/secrets")
        .get<kubeent::status>();
}

kubeent::secret secret::read(const std::string namespace_,
                             const std::string name)
{
    return this->get_request("/api/v1/namespaces/"
                             + namespace_
                             + "/secrets/"
                             + name)
        .get<kubeent::secret>();
}


kubeent::secret_list secret::list(const std::string namespace_)
{
    return this->get_request("/api/v1/namespaces/"
                             + namespace_
                             + "/secrets")
        .get<kubeent::secret_list>();
}

}
}
