#include "process/gateway.hpp"
#include "http_client/curl_helper.hpp"
#include "kubeent/deployment.hpp"
#include "kubeent/service.hpp"
#include "kubeent/service_list.hpp"
#include "kube_api/deployment.hpp"
#include "kube_api/service.hpp"

namespace navagraha {
namespace process {

gateway::gateway(cli::config & cfg)
    : config(cfg)
{

}

std::string gateway::set(const gateway_set_arg & arg)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    this->create_deployment(arg, helper);
    this->create_service(arg, helper);

    return std::string();
}

void gateway::create_deployment(const gateway_set_arg & arg, http_client::curl_helper & helper)
{
    kubeent::deployment req;

    req.api_version = std::string("apps/v1");
    req.kind = std::string("Deployment");
    req.metadata.get().name = std::string("nava-api-gateway");
    req.metadata.get().labels.get().values()["nava_app"] = std::string("nava-api-gateway");
    req.spec.get().replicas.get() = arg.replicas;
    req.spec.get().selector.get().match_labels.get()
        .values()["common_domain"] = std::string("navagraha_apigw_pod");
    req.spec.get().selector.get().match_labels.get()
        .values()["nava_app"] = std::string("nava_apigw");
    req.spec.get().template_.get().spec.get().containers.get().values()
        .push_back(kubeent::container());
    req.spec.get().template_.get().spec.get().containers.get().values().back()
        .name = std::string("nava_apigw");
    req.spec.get().template_.get().spec.get().containers.get().values().back()
        .image = std::string(arg.image);
    req.spec.get().template_.get().spec.get().containers.get().values().back()
        .ports.get().values().push_back(kubeent::container_port());
    req.spec.get().template_.get().spec.get().containers.get().values().back().ports.get().values()
        .back().container_port_ = 80;
    req.spec.get().template_.get().spec.get().containers.get().values().back().env
        .get().values().push_back(kubeent::env_var());
    req.spec.get().template_.get().spec.get().containers.get().values().back().env.get().values().back()
        .name = std::string("FUNC_NAMESPACE");
    req.spec.get().template_.get().spec.get().containers.get().values().back().env.get().values().back()
        .value = std::string(arg.namespace_);

    if (!arg.policy.empty()) {
        req.spec.get().template_.get().spec.get().containers.get().values().back()
            .image_pull_policy = std::string(arg.policy);
    }

    helper.build<kube_api::deployment>().create(arg.namespace_, req);
}

void gateway::create_service(const gateway_set_arg & arg, http_client::curl_helper & helper)
{
    kubeent::service req;

    req.api_version = std::string("v1");
    req.kind = std::string("Service");
    req.metadata.get().name = std::string("nava-api-gateway");
    req.metadata.get().labels.get().values()["common_domain"] = std::string("navagraha_apigw_svc");
    req.spec.get().selector.get().values()["common_domain"] = std::string("navagraha_apigw_pod");
    req.spec.get().selector.get().values()["nava_app"] = std::string("nava_apigw");
    req.spec.get().ports.get().values().push_back(kubeent::service_port());
    req.spec.get().ports.get().values().back().port = 80;

    helper.build<kube_api::service>().create(arg.namespace_, req);
}

char GATEWAY_LIST_ITEM_NAMESPACE[] = "namespace";
char GATEWAY_LIST_ITEM_CLUSTER_IP[] = "clusterIP";

void gateway_list_item::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->namespace_)
        .add(this->cluster_ip);
}

extensions::special_list<gateway_list_item> gateway::get(const gateway_get_arg & arg)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    extensions::special_list<gateway_list_item> ret;

    auto svc_cb = [&ret, &arg] (kubeent::service_list & list) -> void
    {
        for (auto svc : list.items.get().values()) {
            ret.values().push_back(gateway_list_item());

            ret.values().back().cluster_ip = std::string(svc.spec.get().cluster_ip.get());
            ret.values().back().namespace_ = std::string(arg.namespace_);
        }
    };

    helper.build<kube_api::service>()
        .list(arg.namespace_)
        .response_switch()
        .response_case<200, kubeent::service_list>(svc_cb);

    return ret;
}

std::string gateway::remove(const gateway_remove_arg & arg)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    kubeent::delete_options dep_opt;
    kubeent::delete_options svc_opt;

    helper
        .build<kube_api::deployment>()
        .delete_(arg.namespace_, "nava-api-gateway", dep_opt);
    helper
        .build<kube_api::service>()
        .delete_(arg.namespace_, "nava-api-gateway", svc_opt);
    
    return std::string();
}

}
}
