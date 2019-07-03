#include "cli/config.hpp"
#include "cli/gateway_init.hpp"
#include "kubeent/pod.hpp"
#include "kube_api/pod.hpp"

namespace navagraha {
namespace cli {

char CLI_GATEWAY_INIT_FLAG[] = "init";

void gateway_init::bind(cli_arg::process_helper<gateway_init> & helper)
{
    helper
        .add(this->init_flag);
}

bool gateway_init::satisfy() const
{
    return this->init_flag.used();
}


void gateway_init::create_pod(std::string namespace_, http_client::curl_helper & helper)
{
    kubeent::pod pod;

    pod.api_version = std::string("v1");
    pod.kind = std::string("Pod");
    pod.metadata.get().name = std::string("nava-api-gateway");
    pod.metadata.get().namespace_ = std::string(namespace_);
    pod.metadata.get().labels.get().values()["common_domain"] = std::string("navagraha-apigw-pod");
    pod.metadata.get().labels.get().values()["nava_app"] = std::string("nava-apigw");
    pod.spec.get().containers.get().values().push_back(kubeent::container());
    pod.spec.get().containers.get().values().back().name = std::string("nava-apigw");
    pod.spec.get().containers.get().values().back().image = std::string("nava/apigw:v0.1");
    pod.spec.get().containers.get().values().back().ports.get().values().push_back(kubeent::container_port());
    pod.spec.get().containers.get().values().back().ports.get().values().back().container_port_ = 80;

    pod.spec.get().containers.get().values().back().image_pull_policy = "Never"; // TODO 

    helper.build<kube_api::pod>().create(namespace_, pod);
}

int gateway_init::execute()
{
    std::string namespace_ = "default";
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);

    this->create_pod(namespace_, helper);

    return 0;
}


}
}
