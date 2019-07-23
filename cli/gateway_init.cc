#include "cli/config.hpp"
#include "cli/gateway_init.hpp"
#include "kubeent/service.hpp"
#include "kubeent/deployment.hpp"
#include "kube_api/deployment.hpp"
#include "kube_api/service.hpp"

namespace navagraha {
namespace cli {

char CLI_GATEWAY_INIT_FLAG[] = "init";
char CLI_GATEWAY_INIT_IMAGE_PULL_POLICY[] = "--policy";
char CLI_GATEWAY_INIT_NAMESPACE[] = "--namespace";

void gateway_init::bind(cli_arg::process_helper<gateway_init> & helper)
{
    this->image_pull_policy.require(this->init_flag);
    this->namespace_arg.require(this->init_flag);
    helper
        .add(this->init_flag)
        .add(this->image_pull_policy)
        .add(this->namespace_arg);
}

bool gateway_init::satisfy() const
{
    return this->init_flag.used();
}


void gateway_init::create_deployment(std::string namespace_, http_client::curl_helper & helper)
{
    kubeent::deployment deploy;

    deploy.api_version = std::string("apps/v1");
    deploy.kind = std::string("Deployment");
    deploy.metadata.get().name = std::string("nava-api-gateway-deploy");
    deploy.metadata.get().labels.get().values()["nava_app"] = std::string("nava-api-gateway-deploy");
    deploy.spec.get().replicas = 1;
    deploy.spec.get().selector.get().match_labels.get()
        .values()["common_domain"] = std::string("navagraha-apigw-pod");
    deploy.spec.get().selector.get().match_labels.get()
        .values()["nava_app"] = std::string("nava-apigw");
    deploy.spec.get().template_.get().metadata.get().labels.get()
        .values()["common_domain"] = std::string("navagraha-apigw-pod");
    deploy.spec.get().template_.get().metadata.get().labels.get()
        .values()["nava_app"] = std::string("nava-apigw");
    deploy.spec.get().template_.get().spec.get().containers.get().values()
        .push_back(kubeent::container());
    deploy.spec.get().template_.get().spec.get().containers.get().values().front()
        .name = std::string("nava-apigw");
    deploy.spec.get().template_.get().spec.get().containers.get().values().front()
        .image = std::string("nava/apigw:v0.1");
    deploy.spec.get().template_.get().spec.get().containers.get().values().front()
        .ports.get().values().push_back(kubeent::container_port());
    deploy.spec.get().template_.get().spec.get().containers.get().values().front()
        .ports.get().values().front().container_port_ = 80;
    deploy.spec.get().template_.get().spec.get().containers.get().values().front()
        .env.get().values().push_back(kubeent::env_var());
    deploy.spec.get().template_.get().spec.get().containers.get().values().front()
        .env.get().values().front().name = std::string("FUNC_NAMESPACE");
    deploy.spec.get().template_.get().spec.get().containers.get().values().front()
        .env.get().values().front().value = std::string(namespace_);

    if (this->image_pull_policy.used()) {
        deploy.spec.get().template_.get().spec.get().containers.get().values().front()
            .image_pull_policy = std::string(this->image_pull_policy[0]);
    }

    helper.build<kube_api::deployment>()
        .create(namespace_, deploy)
        .response_switch()
        .response_case<201, kubeent::deployment>([] (kubeent::deployment &) -> void { std::cout << "API Gateway pod created." << std::endl; });
}

void gateway_init::create_service(std::string namespace_, http_client::curl_helper & helper)
{
    kubeent::service svc;
    
    svc.api_version = std::string("v1");
    svc.kind = std::string("Service");
    svc.metadata.get().name = std::string("nava-api-gateway");
    svc.metadata.get().labels.get().values()["common_domain"] = std::string("navagraha_apigw_svc");
    svc.spec.get().selector.get().values()["common_domain"] = std::string("navagraha-apigw-pod");
    svc.spec.get().selector.get().values()["nava_app"] = std::string("nava-apigw");
    svc.spec.get().ports.get().values().push_back(kubeent::service_port());
    svc.spec.get().ports.get().values().front().port = 80;

    helper.build<kube_api::service>().create(namespace_, svc)
        .response_switch()
        .response_case<200, kubeent::service>([] (kubeent::service &) -> void { std::cout << "API Gateway service create" << std::endl; })
        .response_case<201, kubeent::service>([] (kubeent::service &) -> void { std::cout << "API Gateway service created" << std::endl; })
        .response_case<202, kubeent::service>([] (kubeent::service &) -> void { std::cout << "Accepted API Gateway service created" << std::endl; });
}

int gateway_init::execute()
{
    std::string namespace_ = "default";
    if (this->namespace_arg.used()) {
        namespace_ = this->namespace_arg[0];
    }
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);

    this->create_deployment(namespace_, helper);
    this->create_service(namespace_, helper);

    return 0;
}


}
}
