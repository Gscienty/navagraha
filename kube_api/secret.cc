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
    return this->post_call<kubeent::secret>("/api/v1/namespaces/"
                                            + namespace_
                                            + "/secrets");
}

kubeent::status secret::delete_(const std::string namespace_,
                                const std::string name,
                                kubeent::delete_options & opts)
{
    this->set_payload(opts);
    return this->delete_call<kubeent::status>("/api/v1/namespaces/"
                                              + namespace_
                                              + "/secrets/"
                                              + name);
}

kubeent::status secret::delete_collecton(const std::string namespace_,
                                         kubeent::delete_options & opts)
{
    this->set_payload(opts);
    return this->delete_call<kubeent::status>("/api/v1/namespaces/"
                                              + namespace_
                                              + "/secrets");
}

kubeent::secret secret::read(const std::string namespace_,
                             const std::string name)
{
    return this->get_call<kubeent::secret>("/api/v1/namespaces/"
                                           + namespace_
                                           + "/secrets/"
                                           + name);
}


kubeent::secret_list secret::list(const std::string namespace_)
{
    return this->get_call<kubeent::secret_list>("/api/v1/namespaces/"
                                                + namespace_
                                                + "/secrets");
}

}
}
