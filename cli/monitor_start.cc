#include "cli/monitor_start.hpp"
#include "cli/config.hpp"
#include "kubeent/namespace.hpp"
#include "kubeent/config_map.hpp"
#include "kubeent/deployment.hpp"
#include "kubeent/service_account.hpp"
#include "kubeent/cluster_role.hpp"
#include "kubeent/cluster_role_binding.hpp"
#include "kube_api/namespace.hpp"
#include "kube_api/config_map.hpp"
#include "kube_api/deployment.hpp"
#include "kube_api/service_account.hpp"
#include "kube_api/cluster_role.hpp"
#include "kube_api/cluster_role_binding.hpp"
#include "extensions/base64.hpp"
#include <string>
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_MONITOR_START_FLAG[] = "start";

void monitor_start::bind(cli_arg::process_helper<monitor_start> & helper)
{
    helper
        .add(this->init_flag);
}

bool monitor_start::satisfy() const
{
    return this->init_flag.used();
}

int monitor_start::execute()
{
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);

    this->init_monitor_namespace(helper);

    this->create_service_account(helper);
    this->create_cluster_role(helper);

    this->create_config_map(helper);

    this->deployment_prometheus(helper);

    this->cluster_role_binding(helper);

    return 0;
}

void monitor_start::init_monitor_namespace(http_client::curl_helper & helper)
{
    kubeent::namespace_ ns;

    ns.api_version = std::string("v1");
    ns.kind = std::string("Namespace");
    ns.metadata.get().name = std::string("nava-monitor");

    helper.build<kube_api::namespace_>().create(ns);
}

void monitor_start::create_config_map(http_client::curl_helper & helper)
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

    helper.build<kube_api::config_map>().create("nava-monitor", cm);
}

void monitor_start::deployment_prometheus(http_client::curl_helper & helper)
{
    kubeent::deployment dep;

    dep.api_version = std::string("apps/v1");
    dep.kind = std::string("Deployment");
    dep.metadata.get().name = std::string("nava-monitor-prometheus");
    dep.spec.get().selector.get().match_labels.get()
        .values()["app"] = std::string("nava-monitor-prometheus-server");
    dep.spec.get().replicas = 1;
    dep.spec.get().template_.get().metadata.get().labels.get()
        .values()["app"] = std::string("nava-monitor-prometheus-server");
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

    helper.build<kube_api::deployment>().create("nava-monitor", dep);
}

void monitor_start::create_service_account(http_client::curl_helper & helper)
{
    kubeent::service_account sa;

    sa.api_version = "v1";
    sa.kind = "ServiceAccount";
    sa.metadata.get().name = std::string("prometheus-sa");

    helper.build<kube_api::service_account>().create("nava-monitor", sa);
}

void monitor_start::create_cluster_role(http_client::curl_helper & helper)
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

void monitor_start::cluster_role_binding(http_client::curl_helper & helper)
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
    binding.subjects.get().values().back().namespace_ = std::string("nava-monitor");

    helper.build<kube_api::cluster_role_binding>().create(binding);
}

}
}
