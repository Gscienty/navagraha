#include "cli/gateway_list.hpp"
#include "cli/config.hpp"
#include "http_client/curl_helper.hpp"
#include "kube_api/pod.hpp"
#include <iostream>
#include <algorithm>

namespace navagraha {
namespace cli {

char CLI_GATEWAY_LIST_FLAG[] = "list";
char CLI_GATEWAY_LIST_NAMESPACE[] = "--namespace";

void gateway_list::bind(cli_arg::process_helper<gateway_list> & helper) 
{
    this->namespace_arg.require(this->list_flag);

    helper
        .add(this->list_flag)
        .add(this->namespace_arg);
}

bool gateway_list::satisfy() const
{
    return this->list_flag.used();
}

int gateway_list::execute()
{

    std::string namespace_ = "default";
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);
    if (this->namespace_arg.used()) {
        namespace_ = this->namespace_arg[0];
    }

    helper.build<kube_api::pod>().list(namespace_)
        .response_switch()
        .response_case<200, kubeent::pod_list>(std::bind(&gateway_list::gateway_pods_foreach,
                                                         this,
                                                         std::placeholders::_1));

    return 0;
}

void gateway_list::gateway_pods_foreach(kubeent::pod_list & pods)
{
    auto eachor = [] (kubeent::pod & pod) -> void {
        auto finded = pod.metadata.get().labels.get().values().find("nava_app");

        if (finded == pod.metadata.get().labels.get().values().end()) {
            return;
        }

        if (finded->second.str == "nava-apigw") {
            std::cout
                << pod.metadata.get().name.get()
                << "\t"
                << pod.status.get().pod_ip.get()
                << std::endl;
        }
    };

    std::for_each(std::begin(pods.items.get().values()), std::end(pods.items.get().values()), eachor);
}

}
}

