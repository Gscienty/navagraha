#ifndef _NAVAGRAHA_KUBE_API_SECRET_H
#define _NAVAGRAHA_KUBE_API_SECRET_H

#include "http_client/client.hpp"
#include "kubeent/secret.hpp"

namespace navagraha {
namespace kube_api {

class secret : public http_client::client {
public:
    secret(CURL * curl, const std::string host);

    kubeent::secret create(const std::string namespace_,
                           kubeent::secret & secret);
};

}
}
#endif
