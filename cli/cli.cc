#include "cli/func.hpp"
#include "cli/project.hpp"
#include "cli/namespace.hpp"
#include "cli/secret.hpp"
#include "cli/config.hpp"
#include "cli/config_map.hpp"
#include "cli/monitor.hpp"
#include "cli/gateway.hpp"
#include "cli/invoke.hpp"
#include "cli/node.hpp"
#include "cli_arg/process_collection.hpp"
#include "cli/cli_usage.hpp"

int main(int argc, char ** argv)
{
    navagraha::cli::config::get_instance().kube_ca = "/etc/kubernetes/pki/ca.crt";
    navagraha::cli::config::get_instance().kube_key = "/etc/kubernetes/pki/apiserver-kubelet-client.key";
    navagraha::cli::config::get_instance().kube_cert = "/etc/kubernetes/pki/apiserver-kubelet-client.crt";
    navagraha::cli::config::get_instance().kube_api_server = "https://localhost:6443";
    navagraha::cli::config::get_instance().docker_sock = "/var/run/docker.sock";

    return navagraha::cli_arg::process_collection(argc, argv)
        .add(navagraha::cli::func())
        .add(navagraha::cli::project())
        .add(navagraha::cli::namespace_())
        .add(navagraha::cli::secret())
        .add(navagraha::cli::monitor())
        .add(navagraha::cli::gateway())
        .add(navagraha::cli::config_map())
        .add(navagraha::cli::node())
        .add(navagraha::cli::invoke())
        .default_process(navagraha::cli::cli_usage())
        .result();
}
