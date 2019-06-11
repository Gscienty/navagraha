#include "cli/monitor_break.hpp"
#include "cli/config.hpp"
#include "kubeent/delete_options.hpp"
#include "kube_api/namespace.hpp"
#include "kube_api/cluster_role.hpp"

namespace navagraha {
namespace cli {

char CLI_MONITOR_BREAK_FLAG[] = "break";

void monitor_break::bind(cli_arg::process_helper<monitor_break> & helper)
{
    helper
        .add(this->break_flag);
}

bool monitor_break::satisfy() const
{
    return this->break_flag.used();
}

int monitor_break::execute()
{
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);
    this->delete_namespace(helper);
    this->delete_cluster_role(helper);
    return 0;
}
void monitor_break::delete_cluster_role(http_client::curl_helper & helper)
{
    kubeent::delete_options opt;

    helper.build<kube_api::cluster_role>().delete_("prometheus-cr", opt);
}

void monitor_break::delete_namespace(http_client::curl_helper & helper)
{
    kubeent::delete_options opt;

    helper.build<kube_api::namespace_>().delete_("nava-monitor", opt);
}

}
}
