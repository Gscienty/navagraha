#include "cli/invoke.hpp"
#include "cli/config.hpp"
#include "http_client/curl_helper.hpp"
#include "kube_api/service.hpp"
#include "kubeent/service_list.hpp"
#include <algorithm>
#include <sstream>
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_INVOKE_NAME[] = "invoke";
char CLI_INVOKE_NAMESPACE[] = "--namespace";
char CLI_INVOKE_PAYLOAD[] = "--payload";

void invoke::bind(cli_arg::process_helper<invoke> & helper)
{
    this->namespace_arg.require(this->invoke_name);
    this->payload_arg.require(this->invoke_name);

    helper
        .add(this->invoke_name)
        .add(this->namespace_arg)
        .add(this->payload_arg);
}

int invoke::execute()
{
    std::string namespace_ = "default";
    std::string gateway_ip = "";
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);
    if (this->namespace_arg.used()) {
        namespace_ = this->namespace_arg[0];
    }

    helper.build<kube_api::service>().list(namespace_)
        .response_switch()
        .response_case<200, kubeent::service_list>([&gateway_ip] (kubeent::service_list &svcs) -> void
                                                   {
                                                   std::for_each(std::begin(svcs.items.get().values()),
                                                                 std::end(svcs.items.get().values()),
                                                                 [&gateway_ip] (kubeent::service & svc) -> void
                                                                 {
                                                                 if (svc.metadata.get().labels.get().values().find("common_domain") != std::end(svc.metadata.get().labels.get().values())
                                                                     && svc.metadata.get().labels.get().values()["common_domain"].str.compare("navagraha_apigw_svc") == 0) {
                                                                    gateway_ip = svc.spec.get().cluster_ip.get();
                                                                 }
                                                                 });
                                                   });

    if (gateway_ip.empty()) {
        return -1;
    }

    std::cout << helper.simple_build("http://" + gateway_ip)
        .post_request("/" + this->invoke_name[0], this->payload_arg[0])
        .result();

    return 0;
}

bool invoke::satisfy() const 
{
    return this->invoke_name.used();
}

}
}
