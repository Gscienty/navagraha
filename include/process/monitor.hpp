#ifndef _NAVAGRAHA_PROCESS_MONITOR_H
#define _NAVAGRAHA_PROCESS_MONITOR_H

#include "cli/config.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace process {

class monitor {
private:
    cli::config & config;

    void set_prometheus_config(http_client::curl_helper & helper, std::string namespace_);
    void set_prometheus_deployment(http_client::curl_helper & helper, std::string namespace_);
    void set_prometheus_service_account(http_client::curl_helper & helper, std::string namespace_);
    void set_prometheus_cluster_role(http_client::curl_helper & helper);
    void set_prometheus_cluster_role_bind(http_client::curl_helper & helper, std::string namespace_);
public:
    monitor(cli::config & config);

    int node_count();
    int namespace_count();
    int func_count();
    int project_count();

    std::string start(std::string namespace_);
};

}
}

#endif
