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
    return this->post_call<kubeent::secret>("/api/v1/namespaces"
                                            + namespace_
                                            + "/secrets");
}

}
}
