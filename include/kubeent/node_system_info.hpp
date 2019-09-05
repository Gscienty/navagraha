#ifndef _NAVAGRAHA_KUBEENT_NODE_SYSTEM_INFO_H
#define _NAVAGRAHA_KUBEENT_NODE_SYSTEM_INFO_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"

namespace navagraha {
namespace kubeent {

extern char NODE_SYSTEM_INFO_ARCHITECTURE[];
extern char NODE_SYSTEM_INFO_BOOT_ID[];
extern char NODE_SYSTEM_INFO_CONTAINER_RUNTIME_VERSION[];
extern char NODE_SYSTEM_INFO_KERNEL_VERSION[];
extern char NODE_SYSTEM_INFO_KUBE_PROXY_VERSION[];
extern char NODE_SYSTEM_INFO_KUBELET_VERSION[];
extern char NODE_SYSTEM_INFO_MACHINE_ID[];
extern char NODE_SYSTEM_INFO_OPERATING_SYSTEM[];
extern char NODE_SYSTEM_INFO_OS_IMAGE[];
extern char NODE_SYSTEM_INFO_SYSTEM_UUID[];

class node_system_info : public extensions::serializable<node_system_info> {
public:
    extensions::field<std::string, NODE_SYSTEM_INFO_ARCHITECTURE> architecture;
    extensions::field<std::string, NODE_SYSTEM_INFO_BOOT_ID> boot_id;
    extensions::field<std::string, NODE_SYSTEM_INFO_CONTAINER_RUNTIME_VERSION> container_runtime_version;
    extensions::field<std::string, NODE_SYSTEM_INFO_KERNEL_VERSION> kernel_version;
    extensions::field<std::string, NODE_SYSTEM_INFO_KUBE_PROXY_VERSION> kube_proxy_version;
    extensions::field<std::string, NODE_SYSTEM_INFO_KUBELET_VERSION> kubelet_version;
    extensions::field<std::string, NODE_SYSTEM_INFO_MACHINE_ID> machine_id;
    extensions::field<std::string, NODE_SYSTEM_INFO_OPERATING_SYSTEM> operating_system;
    extensions::field<std::string, NODE_SYSTEM_INFO_OS_IMAGE> os_image;
    extensions::field<std::string, NODE_SYSTEM_INFO_SYSTEM_UUID> system_uuid;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
