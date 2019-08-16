#include "process/gateway.hpp"
#include "http_client/curl_helper.hpp"
#include "kubeent/deployment.hpp"
#include "kubeent/service.hpp"
#include "kubeent/service_list.hpp"
#include "kube_api/deployment.hpp"
#include "kube_api/service.hpp"
#include "docker_api/images.hpp"
#include "dockerent/image.hpp"
#include <algorithm>

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

extensions::special_list<gateway_repo_list_item> gateway::repo()
{
    extensions::special_list<gateway_repo_list_item> items;

    auto eachor = [&items] (navagraha::extensions::special_list<navagraha::dockerent::image> & images) -> void
    {
        for (auto image : images.values()) {
            if (image.labels.get().values().find(std::string("navaapigw")) == image.labels.get().values().end()) {
                continue;
            }
            std::string fullname = image.repo_tags.get().values().front();
            std::string::iterator tag_spliter = std::find(std::begin(fullname), std::end(fullname), ':');

            items.values().push_back(gateway_repo_list_item());
            if (tag_spliter == std::end(fullname)) {
                items.values().back().name = std::string(fullname);
            }
            else {
                std::string tag_name(std::begin(fullname), tag_spliter);
                tag_spliter++;
                std::string version(tag_spliter, std::end(fullname));

                items.values().back().name = std::string(tag_name);
                items.values().back().version = std::string(version);
            }
        }
    };

    navagraha::http_client::curl_helper(this->config.docker_sock)
        .unix_socket_build<navagraha::docker_api::images>()
        .list()
        .response_switch()
        .response_case<200, navagraha::extensions::special_list<navagraha::dockerent::image>>(eachor);

    return items;
}

char GATEWAY_REPO_LIST_ITEM_NAME[] = "name";
char GATEWAY_REPO_LIST_ITEM_VERSION[] = "version";

void gateway_repo_list_item::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name)
        .add(this->version);
}

}
}
