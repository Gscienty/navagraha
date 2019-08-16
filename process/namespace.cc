#include "process/namespace.hpp"
#include "http_client/curl_helper.hpp"
#include "kube_api/namespace.hpp"

namespace navagraha {
namespace process {

namespace_::namespace_(cli::config & cfg)
    : config(cfg)
{

}

std::string namespace_::add(std::string name)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);
    kubeent::namespace_ ns;
    ns.api_version = std::string("v1");
    ns.kind = std::string("Namespace");
    ns.metadata.get().name = std::string(name);
    ns.metadata.get().labels.get().values()["navagraha_namespace"] = std::string(name);

    helper.build<kube_api::namespace_>().create(ns);
    return std::string();
}

std::string namespace_::remove(std::string name)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);
    kubeent::delete_options opt;
    helper.build<kube_api::namespace_>().delete_(name, opt);
    return std::string();
}

extensions::special_list<namespace_list_item> namespace_::list()
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    extensions::special_list<namespace_list_item> ret;
    auto cb = [&ret] (kubeent::namespace_list & list) -> void
    {
        for (auto & ns : list.items.get().values()) {
            if (ns.metadata.get().labels.get().values().find("navagraha_namespace") == ns.metadata.get().labels.get().values().end()
                && ns.metadata.get().name.get().compare("default") != 0) {
                continue;
            }
            ret.values().push_back(namespace_list_item());
            ret.values().back().name = std::string(ns.metadata.get().name.get());
            ret.values().back().status = std::string(ns.status.get().phase.get());
        }
    };

    helper.build<kube_api::namespace_>().list()
        .response_switch()
        .response_case<200, kubeent::namespace_list>(cb);

    return ret;
}

char NAMESPACE_LIST_ITEM_NAME[] = "name";
char NAMESPACE_LIST_ITEM_STATUS[] = "status";

void namespace_list_item::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name)
        .add(this->status);
}

}
}
