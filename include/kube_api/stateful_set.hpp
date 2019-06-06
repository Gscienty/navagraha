#ifndef _NAVAGRAHA_KUBE_API_STATEFUL_SET_H
#define _NAVAGRAHA_KUBE_API_STATEFUL_SET_H

#include "http_client/client.hpp"
#include "kubeent/stateful_set.hpp"
#include "kubeent/status.hpp"
#include "kubeent/delete_options.hpp"

namespace navagraha {
namespace kube_api {

class stateful_set : public http_client::client {
public:
    stateful_set(CURL * curl, const std::string host);

    kubeent::stateful_set create(const std::string namespace_,
                                 kubeent::stateful_set & stateful_set_);

    kubeent::status delete_(const std::string namespace_,
                            const std::string name,
                            kubeent::delete_options & options);

    kubeent::status delete_collection(const std::string namespace_);

    kubeent::stateful_set read(const std::string namespace_,
                               const std::string name);
};

}
}


#endif
