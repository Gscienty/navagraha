#ifndef _NAVAGRAHA_PROCESS_MONITOR_H
#define _NAVAGRAHA_PROCESS_MONITOR_H

#include "cli/config.hpp"
#include "http_client/curl_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"

namespace navagraha {
namespace process {

extern char MONITOR_GET_RESULT_NAMESPACE[];
extern char MONITOR_GET_RESULT_EXIST[];
extern char MONITOR_GET_RESULT_SERVICE_IP[];

class monitor_get_result : public extensions::serializable<monitor_get_result> {
public:
    extensions::field<std::string, MONITOR_GET_RESULT_NAMESPACE> namespace_;
    extensions::field<bool, MONITOR_GET_RESULT_EXIST> exist;
    extensions::field<std::string, MONITOR_GET_RESULT_SERVICE_IP> service_ip;

    void bind(extensions::serializer_helper & helper);
};

class monitor {
private:
    cli::config & config;

    void set_prometheus_config(http_client::curl_helper & helper, std::string namespace_);
    void set_prometheus_deployment(http_client::curl_helper & helper, std::string namespace_);
    void set_prometheus_service_account(http_client::curl_helper & helper, std::string namespace_);
    void set_prometheus_cluster_role(http_client::curl_helper & helper);
    void set_prometheus_cluster_role_bind(http_client::curl_helper & helper, std::string namespace_);
    void set_prometheus_service(http_client::curl_helper & helper, std::string namespace_);
public:
    monitor(cli::config & config);

    int node_count();
    int namespace_count();
    int func_count();
    int project_count();

    std::string start(std::string namespace_);
    monitor_get_result get(std::string namespace_);
    std::string remove(std::string namespace_);
};

}
}

#endif
