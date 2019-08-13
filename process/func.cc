#include "process/func.hpp"
#include "http_client/curl_helper.hpp"
#include "kubeent/deployment.hpp"
#include "kube_api/deployment.hpp"
#include "kubeent/service.hpp"
#include "kube_api/service.hpp"

#include <iostream>
#include <sstream>

namespace navagraha {
namespace process {


func::func(cli::config & cfg)
    : config(cfg)
{

}


std::string func::up(const args::func_up & func_up)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    if (func_up.stateful) {
    }
    else {
        this->func_up_create_deployment(helper, func_up);
        this->func_up_create_service(helper, func_up);
    }


    return std::string();
}

void func::func_up_create_service(http_client::curl_helper & helper,
                                  const args::func_up & func_up)
{
    kubeent::service req;
    req.api_version = std::string("v1");
    req.kind = std::string("Service");
    req.metadata.get().name = std::string(func_up.name);
    req.metadata.get().labels.get().values()["common_domain"] = std::string("navagraha_func_svc");
    req.metadata.get().labels.get().values()["nava_app"] = std::string("navagraha_func");
    req.spec.get().selector.get().values()["common_domain"] = std::string("navagraha_func");
    req.spec.get().selector.get().values()["nava_app"] = std::string(func_up.name);
    req.spec.get().ports.get().values().push_back(kubeent::service_port());
    req.spec.get().ports.get().values().front().port = 80;

    helper.build<kube_api::service>().create(func_up.namespace_, req);
}

void func::func_up_create_deployment(http_client::curl_helper & helper,
                                     const args::func_up & func_up)
{
    kubeent::deployment req;

    req.api_version = std::string("apps/v1");
    req.kind = std::string("Deployment");
    req.metadata.get().name = std::string(func_up.name);
    req.metadata.get().labels.get().values()["nava_app"] = std::string(func_up.name);
    req.spec.get().replicas.get() = func_up.replicas;
    req.spec.get().selector.get().match_labels.get()
        .values()["nava_app"] = std::string(func_up.name);

    req.spec.get().template_.get().metadata.get().labels.get()
        .values()["nava_app"] = std::string(func_up.name);
    req.spec.get().template_.get().metadata.get().labels.get()
        .values()["common_domain"] = std::string("navagraha_func");
    req.spec.get().template_.get().metadata.get().annotations.get()
        .values()["prometheus.io/path"] = std::string("/metrics");
    req.spec.get().template_.get().metadata.get().annotations.get()
        .values()["prometheus.io/port"] = std::string("80");
    req.spec.get().template_.get().metadata.get().annotations.get()
        .values()["prometheus.io/scrape"] = std::string("true");
    req.spec.get().template_.get().spec.get().containers.get()
        .values().push_back(kubeent::container());
    req.spec.get().template_.get().spec.get().containers.get()
        .values().front().name = std::string(func_up.name);
    req.spec.get().template_.get().spec.get().containers.get()
        .values().front().image = std::string(func_up.image);
    req.spec.get().template_.get().spec.get().containers.get()
        .values().front().ports.get().values().push_back(kubeent::container_port());
    req.spec.get().template_.get().spec.get().containers.get().values().front().ports
        .get().values().front().container_port_ = 80;
    req.spec.get().template_.get().spec.get().containers.get().values().front().env
        .get().values().push_back(kubeent::env_var());
    req.spec.get().template_.get().spec.get().containers.get().values().front().env
        .get().values().front().name = std::string("HUMHA_NAMESPACE");
    req.spec.get().template_.get().spec.get().containers.get().values().front().env
        .get().values().front().value = std::string(func_up.namespace_);

    if (!func_up.policy.empty()) {
        req.spec.get().template_.get().spec.get().containers.get().values().front()
            .image_pull_policy = std::string(func_up.policy);
    }

    if (func_up.update) {
        req.spec.get().strategy.get().type = std::string("RollingUpdate");
        
        helper.build<kube_api::deployment>().replace(func_up.namespace_, func_up.name, req);
    }
    else {
        helper.build<kube_api::deployment>().create(func_up.namespace_, req);
    }
}

}
}
