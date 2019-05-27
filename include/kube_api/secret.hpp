#ifndef _NAVAGRAHA_KUBE_API_SECRET_H
#define _NAVAGRAHA_KUBE_API_SECRET_H

#include "http_client/client.hpp"
#include "kubeent/secret.hpp"
#include "kubeent/secret_list.hpp"
#include "kubeent/delete_options.hpp"
#include "kubeent/status.hpp"

namespace navagraha {
namespace kube_api {

class secret : public http_client::client {
public:
    secret(CURL * curl, const std::string host);

    kubeent::secret create(const std::string namespace_,
                           kubeent::secret & secret);

    kubeent::status delete_(const std::string namespace_,
                            const std::string name,
                            kubeent::delete_options & opts);

    kubeent::status delete_collecton(const std::string namespace_,
                                     kubeent::delete_options & opts);

    kubeent::secret read(const std::string namespace_,
                         const std::string name);

    kubeent::secret_list list(const std::string namespace_);

};

}
}
#endif
