#include "cli/config.hpp"
#include "cli/namespace_add.hpp"
#include "kubeent/namespace.hpp"
#include "kube_api/namespace.hpp"

namespace navagraha {
namespace cli {

char CLI_NAMESPACE_ADD[] = "add";

void namespace_add::bind(cli_arg::process_helper<namespace_add> & helper)
{
    helper
        .add(this->add_arg);
}

bool namespace_add::satisfy() const
{
    return this->add_arg.used();
}

int namespace_add::execute()
{
    kubeent::namespace_ ns;
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);

    ns.api_version = std::string("v1");
    ns.kind = std::string("Namespace");
    ns.metadata.get().name = std::string(this->add_arg[0]);
    ns.metadata.get().labels.get().values()["name"] = std::string(this->add_arg[0]);

    helper.build<kube_api::namespace_>().create(ns)
        .response_switch()
        .response_case<200, kubeent::namespace_>([] (kubeent::namespace_ & resp) -> void {
                                                 std::cout
                                                     << "create namespace \""
                                                     << resp.metadata.get().name.const_get()
                                                     << "\""
                                                     << std::endl;
                                                 })
        .response_case<201, kubeent::namespace_>([] (kubeent::namespace_ & resp) -> void {
                                                 std::cout
                                                     << "created namespace \""
                                                     << resp.metadata.get().name.const_get()
                                                     << "\""
                                                     << std::endl;
                                                 })
        .response_case<201, kubeent::namespace_>([] (kubeent::namespace_ & resp) -> void {
                                                 std::cout
                                                     << "accepted create namespace \""
                                                     << resp.metadata.get().name.const_get()
                                                     << "\""
                                                     << std::endl;
                                                 });

    return 0;
}

}
}
