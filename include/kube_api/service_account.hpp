#ifndef _NAVAGRAHA_KUBE_API_SERVICE_ACCOUNT_H
#define _NAVAGRAHA_KUBE_API_SERVICE_ACCOUNT_H

#include "http_client/client.hpp"
#include "kubeent/service_account.hpp"
#include "kubeent/delete_options.hpp"
#include "kubeent/status.hpp"

namespace navagraha {
namespace kube_api {

class service_account : public  http_client::client {
public:
    service_account(CURL * curl, const std::string host);

    kubeent::service_account create(const std::string namespace_,
                                    kubeent::service_account & account);

    kubeent::status delete_(const std::string namespace_,
                            const std::string name,
                            kubeent::delete_options & opts);

    kubeent::status delete_collection(const std::string namespace_);
};

}
}

#endif
