#include "kube_api/service_account.hpp"

namespace navagraha {
namespace kube_api {

service_account::service_account(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

kubeent::service_account service_account::create(const std::string namespace_,
                                                 kubeent::service_account & account)
{
    this->set_payload(account);

    return this->post_request("/api/v1/namespaces/"
                              + namespace_
                              + "/serviceaccounts")
        .get<kubeent::service_account>();
}

kubeent::status service_account::delete_(const std::string namespace_,
                                         const std::string name,
                                         kubeent::delete_options & opts)
{
    this->set_payload(opts);

    return this->delete_request("/api/v1/namespaces/"
                                + namespace_
                                + "/serviceaccounts/"
                                + name)
        .get<kubeent::status>();
}

kubeent::status service_account::delete_collection(const std::string namespace_)
{
    return this->delete_request("/api/v1/namespaces/"
                                + namespace_
                                + "/serviceaccounts")
        .get<kubeent::status>();
}

}
}
