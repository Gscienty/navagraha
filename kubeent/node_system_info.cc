#include "kubeent/node_system_info.hpp"

namespace navagraha {
namespace kubeent {

char NODE_SYSTEM_INFO_ARCHITECTURE[] = "architecture";
char NODE_SYSTEM_INFO_BOOT_ID[] = "bootID";
char NODE_SYSTEM_INFO_CONTAINER_RUNTIME_VERSION[] = "containerRuntimeVersion";
char NODE_SYSTEM_INFO_KERNEL_VERSION[] = "kernelVersion";
char NODE_SYSTEM_INFO_KUBE_PROXY_VERSION[] = "kubeProxyVersion";
char NODE_SYSTEM_INFO_MACHINE_ID[] = "machineID";
char NODE_SYSTEM_INFO_OPERATING_SYSTEM[] = "operatingSystem";
char NODE_SYSTEM_INFO_OS_IMAGE[] = "osImage";
char NODE_SYSTEM_INFO_SYSTEM_UUID[] = "systemUUID";

void node_system_info::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->architecture)
        .add(this->boot_id)
        .add(this->container_runtime_version)
        .add(this->kernel_version)
        .add(this->kube_proxy_version)
        .add(this->machine_id)
        .add(this->operating_system)
        .add(this->os_image)
        .add(this->system_uuid);
}

}
}
