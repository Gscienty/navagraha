#include "cli/func_build.hpp"
#include "cli/func_deploy.hpp"
#include "cli/func_offline.hpp"
#include "cli/project_init.hpp"
#include "cli_arg/process_collection.hpp"
#include "cli/config.hpp"

int main(int argc, char ** argv)
{
    navagraha::cli::config::get_instance().kube_ca = "/etc/kubernetes/pki/ca.crt";
    navagraha::cli::config::get_instance().kube_key = "/etc/kubernetes/pki/apiserver-kubelet-client.key";
    navagraha::cli::config::get_instance().kube_cert = "/etc/kubernetes/pki/apiserver-kubelet-client.crt";
    navagraha::cli::config::get_instance().kube_api_server = "https://localhost:6443";
    navagraha::cli::config::get_instance().docker_sock = "/var/run/docker.sock";

    return navagraha::cli_arg::process_collection(argc, argv)
        .add(navagraha::cli::func_build())
        .add(navagraha::cli::func_deploy())
        .add(navagraha::cli::func_offline())
        .add(navagraha::cli::project_init())
        .result();
}
