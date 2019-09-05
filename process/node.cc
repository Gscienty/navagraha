#include "process/node.hpp"
#include "http_client/curl_helper.hpp"
#include "kube_api/node.hpp"
#include "kubeent/node_list.hpp"
#include <sstream>

namespace navagraha {
namespace process {

node::node(cli::config & config)
    : config(config)
{

}

extensions::special_list<node_list_item> node::list()
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);
    extensions::special_list<node_list_item> ret;
    auto node_cb = [&ret] (kubeent::node_list & list) -> void
    {
        for (auto & node : list.items.get().values()) {
            ret.values().push_back(node_list_item());

            ret.values().back().architecture = std::string(node.status.get().node_info.get().architecture.get());
            ret.values().back().container_runtime_version = std::string(node.status.get().node_info.get().container_runtime_version.get());
            ret.values().back().kernel_version = std::string(node.status.get().node_info.get().kernel_version.get());
            ret.values().back().kubelet_version = std::string(node.status.get().node_info.get().kubelet_version.get());
            ret.values().back().name = std::string(node.metadata.get().name.get());
            ret.values().back().os = std::string(node.status.get().node_info.get().operating_system.get());
            ret.values().back().os_image = std::string(node.status.get().node_info.get().os_image.get());
            ret.values().back().status = std::string(node.status.get().phase.get());
        }

        std::ostringstream oss;
        list.serialize(oss);
        std::cout << oss.str() << std::endl;
    };

    helper.build<kube_api::node>()
        .list()
        .response_switch()
        .response_case<200, kubeent::node_list>(node_cb);
    return ret;
}

char NODE_LIST_ITEM_NAME[] = "name";
char NODE_LIST_ITEM_STATUS[] = "status";
char NODE_LIST_ITEM_ARCHITECTURE[] = "architecture";
char NODE_LIST_ITEM_CONTAINER_RUNTIME_VERSION[] = "containerRuntimeVersion";
char NODE_LIST_ITEM_KERNEL_VERSION[] = "kernelVersion";
char NODE_LIST_ITEM_KUBE_PROXY_VERSION[] = "kubeProxyVersion";
char NODE_LIST_ITEM_KUBELET_VERSION[] = "kubeletVersion";
char NODE_LIST_ITEM_OS[] = "os";
char NODE_LIST_ITEM_OS_IMAGE[] = "osImage";

void node_list_item::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->architecture)
        .add(this->container_runtime_version)
        .add(this->kernel_version)
        .add(this->kubelet_version)
        .add(this->kube_proxy_version)
        .add(this->name)
        .add(this->os)
        .add(this->os_image)
        .add(this->status);
}

}
}
