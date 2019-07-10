#include "cli/namespace_remove.hpp"
#include "cli/config.hpp"
#include "kubeent/delete_options.hpp"
#include "kube_api/namespace.hpp"
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_NAMESPACE_REMOVE[] = "remove";

void namespace_remove::bind(cli_arg::process_helper<namespace_remove> & helper)
{
    helper
        .add(this->remove_arg);
}

bool namespace_remove::satisfy() const
{
    return this->remove_arg.used();
}

int namespace_remove::execute()
{
    kubeent::delete_options opt;
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);
    
    helper.build<kube_api::namespace_>().delete_(this->remove_arg[0], opt)
        .response_switch()
        .response_case<200, kubeent::status>([] (kubeent::status & s) -> void {
                                              std::cout
                                                  << s.message.get();
                                             })
        .response_case<202, kubeent::status>([] (kubeent::status & s) -> void {
                                              std::cout
                                                  << s.message.get();
                                             });

    return 0;
}

}
}
