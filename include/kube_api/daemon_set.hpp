#ifndef _NAVAGRAHA_KUBE_API_DAEMON_SET_H
#define _NAVAGRAHA_KUBE_API_DAEMON_SET_H

#include "http_client/client.hpp"
#include "kubeent/daemon_set.hpp"
#include "kubeent/daemon_set_list.hpp"
#include "kubeent/delete_options.hpp"
#include "kubeent/status.hpp"

namespace navagraha {
namespace kube_api {

class daemon_set : public http_client::client {
public:
    daemon_set(CURL * curl, const std::string host);

    kubeent::daemon_set create(const std::string namespace_,
                               kubeent::daemon_set & daemon_set_);

    kubeent::daemon_set replace(const std::string namespace_,
                                const std::string name,
                                kubeent::daemon_set & daemon_set_);

    kubeent::status delete_(const std::string namespace_,
                            const std::string name,
                            kubeent::delete_options & options);

    kubeent::status delete_collection(const std::string namespace_);

    kubeent::daemon_set read(const std::string namespace_,
                             const std::string name);

    kubeent::daemon_set_list list(const std::string namespace_);

    kubeent::daemon_set_list list_all_namespace();

};

}
}

#endif
