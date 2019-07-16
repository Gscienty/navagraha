#include "cli/func_list.hpp"
#include "kube_api/service.hpp"
#include "kube_api/deployment.hpp"
#include "kubeent/service_list.hpp"
#include "kubeent/deployment_list.hpp"
#include "http_client/curl_helper.hpp"
#include "cli/config.hpp"
#include <map>
#include <functional>
#include <algorithm>
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_FUNC_LIST_NAME[] = "list";
char CLI_FUNC_LIST_NAMESPACE[] = "--namespace";


void func_list::bind(cli_arg::process_helper<func_list> & helper)
{
    this->namespace_arg.require(this->name_arg);

    helper
        .add(this->name_arg)
        .add(this->namespace_arg);
}

bool func_list::satisfy() const
{
    return this->name_arg.used();
}

void func_list::func_service_eachor(std::map<std::string, kubeent::service> svc_map, kubeent::service & svc)
{
    if (svc.metadata.get().labels.get().values()["common_domain"].str == "navagraha_func_svc") {
        svc_map[svc.metadata.get().name.get()] = svc;
    }
}
void func_list::func_deployment_eachor(std::map<std::string, kubeent::service> svc_map, kubeent::deployment & dep)
{
    if (svc_map.find(dep.metadata.get().name.get()) != svc_map.end()) {
        std::cout
            << dep.metadata.get().name.get()
            << "/"
            << dep.status.get().replicas.get()
            << "/"
            << dep.status.get().ready_replicas.get()
            << "/"
            << dep.status.get().updated_replicas.get()
            << "/"
            << dep.status.get().available_replicas.get()
            << "/"
            << dep.status.get().unavailable_replicas.get()
            << std::endl;
    }
}

int func_list::execute()
{
    std::string namespace_ = "default";
    if (this->namespace_arg.used()) {
        namespace_ = this->namespace_arg[0];
    }

    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);

    std::map<std::string, kubeent::service> svc_map;

    helper.build<kube_api::service>().list(namespace_)
        .response_switch()
        .response_case<200, kubeent::service_list>([&svc_map, this] (kubeent::service_list & svcs) -> void {
                                                   std::for_each(std::begin(svcs.items.get().values()),
                                                                 std::end(svcs.items.get().values()),
                                                                 [&svc_map, this] (kubeent::service & svc) -> void {
                                                                 this->func_service_eachor(svc_map, svc);
                                                                 });
                                                   });

    helper.build<kube_api::deployment>().list(namespace_)
        .response_switch()
        .response_case<200, kubeent::deployment_list>([&svc_map, this] (kubeent::deployment_list & deps) -> void {
                                                      std::for_each(std::begin(deps.items.get().values()),
                                                                    std::end(deps.items.get().values()),
                                                                    [&svc_map, this] (kubeent::deployment & dep) -> void {
                                                                    this->func_deployment_eachor(svc_map, dep);
                                                                    });
                                                      });

    return 0;
}

}
}
