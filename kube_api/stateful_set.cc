#include "kube_api/stateful_set.hpp"

namespace navagraha {
namespace kube_api {

stateful_set::stateful_set(CURL * curl, const std::string host)
    : http_client::client(curl, host)
{

}

http_client::http_response stateful_set::create(const std::string namespace_,
                                                kubeent::stateful_set & stateful_set_)
{
    this->set_payload(stateful_set_);
    return this->post_request("/apis/apps/v1/namespaces/"
                              + namespace_
                              + "/statefulsets/");
}

http_client::http_response stateful_set::delete_(const std::string namespace_,
                                                 const std::string name,
                                                 kubeent::delete_options & options)
{
    this->set_payload(options);
    return this->delete_request("/apis/apps/v1/namespaces/"
                                + namespace_
                                + "/statefulsets/"
                                + name);
}

http_client::http_response stateful_set::delete_collection(const std::string namespace_,
                                                           kubeent::delete_options & options)
{
    this->set_payload(options);
    return this->delete_request("/apis/apps/v1/namespaces/"
                                + namespace_
                                + "/statefulsets");
}

http_client::http_response stateful_set::read(const std::string namespace_,
                                              const std::string name)
{
    return this->get_request("/apis/apps/v1/namespaces/"
                             + namespace_
                             + "/statefulsets/"
                             + name);
}

http_client::http_response stateful_set::list(const std::string namespace_)
{
    return this->get_request("/apis/apps/v1/namespaces/"
                             + namespace_
                             + "/statefulsets");
}

http_client::http_response stateful_set::replace(const std::string namespace_,
                                                 const std::string name,
                                                 kubeent::stateful_set & stateful_set_)
{
    this->set_payload(stateful_set_);
    return this->put_request("/apis/apps/v1/namespaces/"
                             + namespace_
                             + "/statefulsets/"
                             + name);
}

}
}
