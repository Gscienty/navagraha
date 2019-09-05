#ifndef _NAVAGRAHA_PROCESS_NODE_H
#define _NAVAGRAHA_PROCESS_NODE_H

#include "cli/config.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"

namespace navagraha {
namespace process {

extern char NODE_LIST_ITEM_NAME[];
extern char NODE_LIST_ITEM_STATUS[];
extern char NODE_LIST_ITEM_ARCHITECTURE[];
extern char NODE_LIST_ITEM_CONTAINER_RUNTIME_VERSION[];
extern char NODE_LIST_ITEM_KERNEL_VERSION[];
extern char NODE_LIST_ITEM_KUBE_PROXY_VERSION[];
extern char NODE_LIST_ITEM_KUBELET_VERSION[];
extern char NODE_LIST_ITEM_OS[];
extern char NODE_LIST_ITEM_OS_IMAGE[];

class node_list_item : public extensions::serializable<node_list_item> {
public:
    extensions::field<std::string, NODE_LIST_ITEM_NAME> name;
    extensions::field<std::string, NODE_LIST_ITEM_STATUS> status;
    extensions::field<std::string, NODE_LIST_ITEM_ARCHITECTURE> architecture;
    extensions::field<std::string, NODE_LIST_ITEM_CONTAINER_RUNTIME_VERSION> container_runtime_version;
    extensions::field<std::string, NODE_LIST_ITEM_KERNEL_VERSION> kernel_version;
    extensions::field<std::string, NODE_LIST_ITEM_KUBE_PROXY_VERSION> kube_proxy_version;
    extensions::field<std::string, NODE_LIST_ITEM_KUBELET_VERSION> kubelet_version;
    extensions::field<std::string, NODE_LIST_ITEM_OS> os;
    extensions::field<std::string, NODE_LIST_ITEM_OS_IMAGE> os_image;

    void bind(extensions::serializer_helper & helper);
};

class node {
private:
    cli::config & config;
public:
    node(cli::config & cfg);

    extensions::special_list<node_list_item> list();
};

}
}

#endif
