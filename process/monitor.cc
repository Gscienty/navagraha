#include "process/monitor.hpp"
#include "process/node.hpp"
#include "http_client/curl_helper.hpp"
#include "kube_api/node.hpp"
#include "kube_api/namespace.hpp"
#include "kube_api/service.hpp"
#include "kube_api/config_map.hpp"
#include "kube_api/deployment.hpp"
#include "kube_api/service_account.hpp"
#include "kube_api/cluster_role.hpp"
#include "kube_api/cluster_role_binding.hpp"
#include "kubeent/node_list.hpp"
#include "kubeent/namespace_list.hpp"
#include "kubeent/service_list.hpp"
#include "kubeent/config_map.hpp"
#include "kubeent/deployment.hpp"
#include "kubeent/service_account.hpp"
#include "kubeent/cluster_role.hpp"
#include "kubeent/cluster_role_binding.hpp"
#include "docker_api/images.hpp"
#include "dockerent/image.hpp"

namespace navagraha {
namespace process {

monitor::monitor(cli::config & config)
    : config(config)
{

}

int monitor::node_count()
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    int ret = 0;
    helper.build<kube_api::node>().list()
        .response_switch()
        .response_case<200, kubeent::node_list>([&ret] (kubeent::node_list & list) -> void { ret = list.items.get().values().size(); });

    return ret;
}

int monitor::namespace_count()
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    int ret = 0;

    auto cb = [&ret] (kubeent::namespace_list & list) -> void
    {
        for (auto & ns : list.items.get().values()) {
            if (ns.metadata.get().labels.get().values().find("navagraha_namespace") == ns.metadata.get().labels.get().values().end()
                && ns.metadata.get().name.get().compare("default") != 0) {
                continue;
            }
            ret++;
        }
    };
    helper.build<kube_api::namespace_>().list()
        .response_switch()
        .response_case<200, kubeent::namespace_list>(cb);

    return ret;
}

int monitor::func_count()
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    int ret = 0;

    auto cb = [&ret] (kubeent::service_list & list) -> void
    {
        for (auto & svc : list.items.get().values()) {
            if (svc.metadata.get().labels.get().values()["common_domain"].str == "navagraha_func_svc") {
                ret++;
            }
        }
    };
    helper.build<kube_api::service>()
        .list_all_namespace()
        .response_switch()
        .response_case<200, kubeent::service_list>(cb);
    return ret;
}

int monitor::project_count()
{
    int ret = 0;
    auto cb = [&ret] (extensions::special_list<dockerent::image> & list) -> void
    {
        for (auto & image : list.values()) {
            if (image.labels.get().values().find(std::string("navafunc")) != image.labels.get().values().end()) {
                ret++;
            }
        }
    };
    navagraha::http_client::curl_helper(this->config.docker_sock)
        .unix_socket_build<navagraha::docker_api::images>()
        .list()
        .response_switch()
        .response_case<200, extensions::special_list<dockerent::image>>(cb);
    return ret;
}

std::string monitor::start(std::string namespace_)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    this->set_prometheus_service_account(helper, namespace_);
    this->set_prometheus_cluster_role(helper);

    this->set_prometheus_config(helper, namespace_);
    this->set_prometheus_deployment(helper, namespace_);

    this->set_prometheus_cluster_role_bind(helper, namespace_);
    this->set_prometheus_service(helper, namespace_);

    return "";
}

monitor_get_result monitor::get(std::string namespace_)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);
    monitor_get_result result;

    auto cb = [&result] (kubeent::service & svc) -> void
    {
        result.service_ip = std::string(svc.spec.get().cluster_ip.get());
        result.namespace_ = std::string(svc.metadata.get().namespace_.get());
        result.exist = true;
    };

    helper.build<kube_api::service>()
        .read(namespace_, "nava-monitor-prometheus-server")
        .response_switch()
        .response_case<200, kubeent::service>(cb);

    if (result.exist.omit() == false) {
        result.exist = false;
    }

    return result;
}

void monitor::set_prometheus_config(http_client::curl_helper & helper, std::string namespace_)
{
    kubeent::config_map cm;

    cm.api_version = std::string("v1");
    cm.kind = std::string("ConfigMap");
    cm.metadata.get().name = std::string("nava-prometheus-server-conf");
    cm.metadata.get().labels.get().values()["name"] = std::string("nava-prometheus-server-conf");
    cm.data.get().values()["prometheus.yml"]
        = std::string("global:\\n"
                      "    scrape_interval: 15s\\n"
                      "    evaluation_interval: 15s\\n"
                      "    external_labels:\\n"
                      "        monitor: \'nava-monitor\'\\n"
                      "scrape_configs:\\n"
                      "- job_name: \'kubernetes-apiservers\'\\n"
                      "  kubernetes_sd_configs:\\n"
                      "  - role: endpoints\\n"
                      "  scheme: https\\n"
                      "  tls_config:\\n"
                      "    ca_file: /var/run/secrets/kubernetes.io/serviceaccount/ca.crt\\n"
                      "    insecure_skip_verify: true\\n"
                      "  bearer_token_file: /var/run/secrets/kubernetes.io/serviceaccount/token\\n"
                      "  relabel_configs:\\n"
                      "  - source_labels: [__meta_kubernetes_namespace, __meta_kubernetes_service_name, __meta_kubernetes_endpoint_port_name]\\n"
                      "    action: keep\\n"
                      "    regex: default;kubernetes;https\\n"
                      "- job_name: \'kubernetes-pods\'\\n"
                      "  kubernetes_sd_configs:\\n"
                      "  - role: pod\\n"
                      "  relabel_configs:\\n"
                      "  - source_labels: [__meta_kubernetes_pod_annotation_prometheus_io_scrape]\\n"
                      "    action: keep\\n"
                      "    regex: true\\n"
                      "  - source_labels: [__meta_kubernetes_pod_annotation_prometheus_io_path]\\n"
                      "    action: replace\\n"
                      "    target_label: __metrics_path__\\n"
                      "    regex: (.+)\\n"
                      "  - source_labels: [__address__, __meta_kubernetes_pod_annotation_prometheus_io_port]\\n"
                      "    action: replace\\n"
                      "    regex: ([^:]+)(?::\\\\d+)?;(\\\\d+)\\n"
                      "    replacement: $1:$2\\n"
                      "    target_label: __address__\\n"
                      "  - action: labelmap\\n"
                      "    regex: __meta_kubernetes_pod_label_(.+)\\n"
                      "  - source_labels: [__meta_kubernetes_namespace]\\n"
                      "    action: replace\\n"
                      "    target_label: kubernetes_namespace\\n"
                      "  - source_labels: [__meta_kubernetes_pod_name]\\n"
                      "    action: replace\\n"
                      "    target_label: kubernetes_pod_name\\n");

    helper.build<kube_api::config_map>().create(namespace_, cm);

}

void monitor::set_prometheus_deployment(http_client::curl_helper & helper, std::string namespace_)
{
    kubeent::deployment dep;

    dep.api_version = std::string("apps/v1");
    dep.kind = std::string("Deployment");
    dep.metadata.get().name = std::string("nava-monitor-prometheus");
    dep.spec.get().selector.get().match_labels.get()
        .values()["nava_app"] = std::string("nava-monitor-prometheus-server");
    dep.spec.get().replicas = 1;
    dep.spec.get().template_.get().metadata.get().labels.get()
        .values()["nava_app"] = std::string("nava-monitor-prometheus-server");
    dep.spec.get().template_.get().spec.get().containers.get()
        .values().push_back(kubeent::container());
    dep.spec.get().template_.get().spec.get().containers.get()
        .values().back().name = std::string("prometheus");
    dep.spec.get().template_.get().spec.get().containers.get()
        .values().back().image = std::string("prom/prometheus:latest");
    dep.spec.get().template_.get().spec.get().containers.get().values().back().args.get()
        .values().push_back(std::string("--config.file=/etc/prometheus/prometheus.yml"));
    dep.spec.get().template_.get().spec.get().containers.get().values().back().args.get()
        .values().push_back(std::string("--storage.tsdb.path=/prometheus/"));
    dep.spec.get().template_.get().spec.get().containers.get().values().back().ports.get()
        .values().push_back(kubeent::container_port());
    dep.spec.get().template_.get().spec.get().containers.get().values().back().ports.get()
        .values().back().container_port_ = 9090;
    dep.spec.get().template_.get().spec.get().containers.get().values().back().volume_mounts.get()
        .values().push_back(kubeent::volume_mount());
    dep.spec.get().template_.get().spec.get().containers.get().values().back().volume_mounts.get()
        .values().back().name = std::string("prometheus-config-volume");
    dep.spec.get().template_.get().spec.get().containers.get().values().back().volume_mounts.get()
        .values().back().mount_path = std::string("/etc/prometheus/");
    dep.spec.get().template_.get().spec.get().containers.get().values().back().volume_mounts.get()
        .values().push_back(kubeent::volume_mount());
    dep.spec.get().template_.get().spec.get().containers.get().values().back().volume_mounts.get()
        .values().back().name = std::string("prometheus-storage-volume");
    dep.spec.get().template_.get().spec.get().containers.get().values().back().volume_mounts.get()
        .values().back().mount_path = std::string("/prometheus/");
    dep.spec.get().template_.get().spec.get().service_account_name = std::string("prometheus-sa");
    dep.spec.get().template_.get().spec.get().volumes.get()
        .values().push_back(kubeent::volume());
    dep.spec.get().template_.get().spec.get().volumes.get()
        .values().back().name = std::string("prometheus-config-volume");
    dep.spec.get().template_.get().spec.get().volumes.get()
        .values().back().config_map.get().default_mode = 420;
    dep.spec.get().template_.get().spec.get().volumes.get()
        .values().back().config_map.get().name = std::string("nava-prometheus-server-conf");
    dep.spec.get().template_.get().spec.get().volumes.get()
        .values().push_back(kubeent::volume());
    dep.spec.get().template_.get().spec.get().volumes.get()
        .values().back().name = std::string("prometheus-storage-volume");
    dep.spec.get().template_.get().spec.get().volumes.get()
        .values().back().empty_dir.get();

    helper.build<kube_api::deployment>().create(namespace_, dep);
}

void monitor::set_prometheus_service_account(http_client::curl_helper & helper, std::string namespace_)
{
    kubeent::service_account sa;
    sa.api_version = "v1";
    sa.kind = "ServiceAccount";
    sa.metadata.get().name = std::string("prometheus-sa");
    helper.build<kube_api::service_account>().create(namespace_, sa);
}

void monitor::set_prometheus_cluster_role(http_client::curl_helper & helper)
{
    kubeent::cluster_role cr;

    cr.api_version = std::string("rbac.authorization.k8s.io/v1");
    cr.metadata.get().name = std::string("prometheus-cr");
    cr.rules.get().values().push_back(kubeent::policy_rule());
    cr.rules.get().values().back().api_groups.get().values().push_back("");
    cr.rules.get().values().back().resources.get().values().push_back("nodes");
    cr.rules.get().values().back().resources.get().values().push_back("nodes/proxy");
    cr.rules.get().values().back().resources.get().values().push_back("services");
    cr.rules.get().values().back().resources.get().values().push_back("endpoints");
    cr.rules.get().values().back().resources.get().values().push_back("pods");
    cr.rules.get().values().back().verbs.get().values().push_back("get");
    cr.rules.get().values().back().verbs.get().values().push_back("list");
    cr.rules.get().values().back().verbs.get().values().push_back("watch");

    cr.rules.get().values().push_back(kubeent::policy_rule());
    cr.rules.get().values().back().non_resource_urls.get().values().push_back("/metrics");
    cr.rules.get().values().back().verbs.get().values().push_back("get");

    helper.build<kube_api::cluster_role>().create(cr);
}

void monitor::set_prometheus_cluster_role_bind(http_client::curl_helper & helper, std::string namespace_)
{
    kubeent::cluster_role_binding binding;

    binding.api_version = std::string("rbac.authorization.k8s.io/v1");
    binding.kind = "ClusterRoleBinding";
    binding.metadata.get().name = std::string("prometheus-crb");
    binding.role_ref_.get().api_group = std::string("rbac.authorization.k8s.io");
    binding.role_ref_.get().kind = std::string("ClusterRole");
    binding.role_ref_.get().name = std::string("prometheus-cr");
    binding.subjects.get().values().push_back(kubeent::subject());
    binding.subjects.get().values().back().kind = std::string("ServiceAccount");
    binding.subjects.get().values().back().name = std::string("prometheus-sa");
    binding.subjects.get().values().back().namespace_ = std::string(namespace_);

    helper.build<kube_api::cluster_role_binding>().create(binding);
}

void monitor::set_prometheus_service(http_client::curl_helper & helper, std::string namespace_)
{
    kubeent::service req;
    req.api_version = std::string("v1");
    req.kind = std::string("Service");
    req.metadata.get().name = std::string("nava-monitor-prometheus-server");
    req.metadata.get().labels.get().values()["common_domain"] = std::string("navagraha_monitor_svc");
    req.metadata.get().labels.get().values()["nava_app"] = std::string("navagraha_monitor");
    req.spec.get().selector.get().values()["nava_app"] = std::string("nava-monitor-prometheus-server");
    req.spec.get().ports.get().values().push_back(kubeent::service_port());
    req.spec.get().ports.get().values().front().port = 9090;
    req.spec.get().ports.get().values().front().target_port = 9090;


    helper.build<kube_api::service>().create(namespace_, req);
}

std::string monitor::remove(std::string namespace_)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    kubeent::delete_options dep_opt;
    helper.build<kube_api::deployment>()
        .delete_(namespace_, "nava-monitor-prometheus", dep_opt);

    kubeent::delete_options svc_opt;
    helper.build<kube_api::service>()
        .delete_(namespace_, "nava-monitor-prometheus-server", svc_opt);

    return "";
}

char MONITOR_GET_RESULT_NAMESPACE[] = "namespace";
char MONITOR_GET_RESULT_EXIST[] = "exist";
char MONITOR_GET_RESULT_SERVICE_IP[] = "serviceIP";

void monitor_get_result::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->namespace_)
        .add(this->exist)
        .add(this->service_ip);
}

}
}
