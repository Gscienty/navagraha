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

    kubeent::namespace_ read(const std::string name);
    kubeent::namespace_list list();

    kubeent::namespace_ create(kubeent::namespace_ & payload);
    kubeent::namespace_ put(const std::string name, kubeent::namespace_ & payload);
    kubeent::status delete_(const std::string name, kubeent::delete_options & opt);
};

}
}

#endif
