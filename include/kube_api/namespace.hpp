#ifndef _NAVAGRAHA_KUBE_API_NAMESPACE_H
#define _NAVAGRAHA_KUBE_API_NAMESPACE_H

#include "http_client/client.hpp"
#include "kubeent/namespace.hpp"
#include "kubeent/namespace_list.hpp"
#include "kubeent/delete_options.hpp"
#include "kubeent/status.hpp"

namespace navagraha {
namespace kube_api {

class namespace_ : public http_client::client {
public:
    namespace_(CURL * curl, const std::string host);

    http_client::http_response read(const std::string name);
    http_client::http_response list();

    http_client::http_response create(kubeent::namespace_ & payload);
    http_client::http_response put(const std::string name, kubeent::namespace_ & payload);
    http_client::http_response delete_(const std::string name, kubeent::delete_options & opt);
};

}
}

#endif
