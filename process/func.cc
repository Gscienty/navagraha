#include "process/func.hpp"
#include "http_client/curl_helper.hpp"
#include "kubeent/deployment.hpp"
#include "kubeent/stateful_set_list.hpp"
#include "kubeent/service.hpp"
#include "kubeent/stateful_set.hpp"
#include "kubeent/horizontal_pod_autoscaler.hpp"
#include "kubeent/horizontal_pod_autoscaler_list.hpp"
#include "kubeent/pod_list.hpp"
#include "kube_api/deployment.hpp"
#include "kube_api/service.hpp"
#include "kube_api/stateful_set.hpp"
#include "kube_api/horizontal_pod_autoscaler.hpp"
#include "kube_api/pod.hpp"
#include "docker_api/images.hpp"
#include <algorithm>

namespace navagraha {
namespace process {


func::func(cli::config & cfg)
    : config(cfg)
{

}


std::string func::up(const func_up_arg & func_up)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    if (func_up.stateful) {
        this->func_up_create_service(helper, func_up);
    }
    else {
        this->func_up_create_deployment(helper, func_up);
        this->func_up_create_service(helper, func_up);
    }


    return std::string();
}

void func::func_up_create_service(http_client::curl_helper & helper,
                                  const func_up_arg & func_up)
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
                                     const func_up_arg & func_up)
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

void func::func_up_create_statefulset(http_client::curl_helper & helper,
                                      const func_up_arg & func_up)
{
    kubeent::stateful_set req;

    req.api_version = std::string("apps/v1");
    req.kind = std::string("StatefulSet");
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
    req.spec.get().template_.get().spec.get().containers.get().values()
        .front().name = std::string(func_up.name);
    req.spec.get().template_.get().spec.get().containers.get().values()
        .front().image = std::string(func_up.image);
    req.spec.get().template_.get().spec.get().containers.get().values()
        .front().ports.get().values().push_back(kubeent::container_port());

    if (!func_up.policy.empty()) {
        req.spec.get().template_.get().spec.get().containers.get().values().front()
            .image_pull_policy = std::string(func_up.policy);
    }

    if (func_up.update) {
        req.spec.get().update_strategy.get().type = std::string("RollingUpdate");
        
        helper.build<kube_api::stateful_set>().replace(func_up.namespace_, func_up.name, req);
    }
    else {
        helper.build<kube_api::stateful_set>().create(func_up.namespace_, req);
    }
}

std::string func::down(const func_down_arg & func_down)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    if (func_down.stateful) {
        kubeent::delete_options stateful_del_ops;
        helper.build<kube_api::stateful_set>().delete_(func_down.namespace_,
                                                       func_down.name,
                                                       stateful_del_ops);

        kubeent::delete_options service_del_ops;
        helper.build<kube_api::service>().delete_(func_down.namespace_,
                                                  func_down.name,
                                                  service_del_ops);
    }
    else {
        kubeent::delete_options service_del_ops;
        helper.build<kube_api::service>().delete_(func_down.namespace_,
                                                  func_down.name,
                                                  service_del_ops);

        kubeent::delete_options deploy_del_ops;
        helper.build<kube_api::deployment>().delete_(func_down.namespace_,
                                                     func_down.name,
                                                     deploy_del_ops);
    }


    return std::string();
}
    
extensions::special_list<func_repo_item> func::repo()
{
    navagraha::extensions::special_list<func_repo_item> items;

    auto eachor = [&items, this] (navagraha::extensions::special_list<navagraha::dockerent::image> & images) -> void 
    {
        std::map<std::string, std::list<std::string>> stored;
        for (auto & image : images.values()) {
            this->func_repo_image_filter(stored, image);
        }

        for (auto & pair : stored) {
            items.values().push_back(func_repo_item());

            items.values().back().name = std::string(pair.first);
            for (auto & version : pair.second) {
                items.values().back().versions.get().values().push_back(version);
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

int func::repoRemove(const std::string name)
{
    return navagraha::http_client::curl_helper(this->config.docker_sock)
        .unix_socket_build<navagraha::docker_api::images>()
        .remove(name)
        .status_code();
}

extensions::special_list<func_list_item> func::list(const func_list_arg & arg)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    navagraha::extensions::special_list<func_list_item> items;

    std::map<std::string, kubeent::service> svc_stored;

    auto svc_store_cb = [&svc_stored] (kubeent::service_list & list) -> void
    {
        for (auto & svc : list.items.get().values()) {
            if (svc.metadata.get().labels.get().values()["common_domain"].str == "navagraha_func_svc") {
                svc_stored[svc.metadata.get().name.get()] = svc;
            }
        }
    };

    helper.build<kube_api::service>()
        .list(arg.namespace_)
        .response_switch()
        .response_case<200, kubeent::service_list>(svc_store_cb);

    auto deploy_list_cb = [&svc_stored, &items, &arg] (kubeent::deployment_list & deps) -> void
    {
        for (auto & dep : deps.items.get().values()) {
            if (svc_stored.find(dep.metadata.get().name.get()) != svc_stored.end()) {
                items.values().push_back(func_list_item());

                items.values().back().name = std::string(dep.metadata.get().name.get());
                items.values().back().namespace_ = std::string(arg.namespace_);
                items.values().back().image_tag = std::string(dep.spec.get().template_.get().spec.get().containers.get().values().front().image.get());
                items.values().back().replicas.get() = dep.status.get().replicas.omit()
                    ? dep.status.get().replicas.get()
                    : 0;
                items.values().back().available.get() = dep.status.get().available_replicas.omit()
                    ? dep.status.get().available_replicas.get()
                    : 0;
                items.values().back().unavailable.get() = dep.status.get().unavailable_replicas.omit()
                    ? dep.status.get().unavailable_replicas.get()
                    : 0;
                items.values().back().stateful.get() = false;
            }
        }
    };

    helper.build<kube_api::deployment>()
        .list(arg.namespace_)
        .response_switch()
        .response_case<200, kubeent::deployment_list>(deploy_list_cb);

    auto stateful_list_cb = [&svc_stored, &items, &arg] (kubeent::stateful_set_list & list) -> void
    {
        for (auto & stateful : list.items.get().values()) {
            if (svc_stored.find(stateful.metadata.get().name.get()) != svc_stored.end()) {
                items.values().push_back(func_list_item());

                items.values().back().name = std::string(stateful.metadata.get().name.get());
                items.values().back().namespace_ = std::string(arg.namespace_);
                items.values().back().image_tag = std::string(stateful.spec.get().template_.get().spec.get().containers.get().values().front().image.get());
                items.values().back().replicas.get() = stateful.status.get().replicas.omit()
                    ? stateful.status.get().replicas.get()
                    : 0;
                items.values().back().available.get() = stateful.status.get().current_replicas.omit()
                    ? stateful.status.get().current_replicas.get()
                    : 0;
                items.values().back().unavailable.get() = 0;
                items.values().back().stateful.get() = true;
            }
        }
    };

    helper.build<kube_api::stateful_set>()
        .list(arg.namespace_)
        .response_switch()
        .response_case<200, kubeent::stateful_set_list>(stateful_list_cb);

    return items;
}

extensions::special_list<func_pod_list_item> func::list_pod(const func_pod_list_arg & arg)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    extensions::special_list<func_pod_list_item> ret;

    auto eachor = [&ret, &arg] (kubeent::pod_list & list) -> void
    {
        for (auto & pod : list.items.get().values()) {
            if (pod.metadata.get().labels.get().values().find("nava_app") == pod.metadata.get().labels.get().values().end()) {
                continue;
            }
            if (pod.metadata.get().labels.get().values()["nava_app"].str.compare(arg.name) != 0) {
                continue;
            }

            ret.values().push_back(func_pod_list_item());

            ret.values().back().name = std::string(pod.metadata.get().name.get());
            ret.values().back().namespace_ = std::string(pod.metadata.get().namespace_.get());
            ret.values().back().image = std::string(pod.status.get().container_statuses.get().values().front().image.get());
            ret.values().back().node = std::string(pod.spec.get().node_name.get());
            ret.values().back().policy = std::string(pod.spec.get().containers.get().values().back().image_pull_policy.get());
            ret.values().back().status = std::string(pod.status.get().phase.get());
        }
    };

    helper.build<kube_api::pod>()
        .list(arg.namespace_)
        .response_switch()
        .response_case<200, kubeent::pod_list>(eachor);

    return ret;
}

std::string func::autoscaling(const func_autoscaling_arg & arg)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    kubeent::horizontal_pod_autoscaler hpa;
    hpa.api_version = "autoscaling/v1";
    hpa.kind = "HorizontalPodAutoscaler";
    hpa.metadata.get().name = std::string(arg.name);
    hpa.metadata.get().labels.get().values()["nava_hpa"] = std::string(arg.name);
    hpa.spec.get().cpu_utilization_percentage.get() = arg.cpu;
    hpa.spec.get().min_replicas.get() = arg.min;
    hpa.spec.get().max_replicas.get() = arg.max;
    hpa.spec.get().scale_target_ref.get().api_version = std::string("apps/v1");
    hpa.spec.get().scale_target_ref.get().kind = std::string("Deployment");
    hpa.spec.get().scale_target_ref.get().name = std::string(arg.name);

    helper.build<kube_api::horizontal_pod_autoscaler>()
        .create(arg.namespace_, hpa);

    return std::string();
}

extensions::special_list<func_autoscaling_list_item> func::list_autoscaling(const func_autoscaling_list_arg & arg)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);

    extensions::special_list<func_autoscaling_list_item> ret;

    auto eachor = [&ret] (kubeent::horizontal_pod_autoscaler_list & list) -> void
    {
        for (auto & hpa : list.items.get().values()) {
            if (hpa.metadata.get().labels.get().values().find("nava_hpa") == hpa.metadata.get().labels.get().values().end()) {
                continue;
            }

            ret.values().push_back(func_autoscaling_list_item());

            ret.values().back().cpu.get() = hpa.spec.get().cpu_utilization_percentage.get();
            ret.values().back().name = std::string(hpa.metadata.get().name.get());
            ret.values().back().max.get() = hpa.spec.get().max_replicas.get();
            ret.values().back().min.get() = hpa.spec.get().min_replicas.get();
            ret.values().back().target.get() = hpa.spec.get().scale_target_ref.get().name.get();
        }
    };

    helper.build<kube_api::horizontal_pod_autoscaler>()
        .list(arg.namespace_)
        .response_switch()
        .response_case<200, kubeent::horizontal_pod_autoscaler_list>(eachor);

    return ret;
}

func_detail func::detail(const func_detail_arg & arg)
{
    http_client::curl_helper helper(this->config.kube_cert,
                                    this->config.kube_key,
                                    this->config.kube_ca,
                                    this->config.kube_api_server);
    func_detail ret;

    if (arg.stateful) {

        return ret;
    }
    else {
        auto deploy_cb = [&ret, &arg] (kubeent::deployment & dep) -> void
        {
            ret.common.get().name = std::string(dep.metadata.get().name.get());
            ret.common.get().namespace_ = std::string(arg.namespace_);
            ret.common.get().image_tag = std::string(dep.spec.get().template_.get().spec.get().containers.get().values().front().image.get());
            ret.common.get().replicas.get() = dep.status.get().replicas.omit()
                ? dep.status.get().replicas.get()
                : 0;
            ret.common.get().available.get() = dep.status.get().available_replicas.omit()
                ? dep.status.get().available_replicas.get()
                : 0;
            ret.common.get().stateful.get() = false;
        };
        helper.build<kube_api::deployment>()
            .read(arg.namespace_, arg.name)
            .response_switch()
            .response_case<200, kubeent::deployment>(deploy_cb);

        auto autoscaling_cb = [&ret] (kubeent::horizontal_pod_autoscaler & hpa) -> void
        {
            ret.autoscaling.get().cpu.get() = hpa.spec.get().cpu_utilization_percentage.get();
            ret.autoscaling.get().name = std::string(hpa.metadata.get().name.get());
            ret.autoscaling.get().max.get() = hpa.spec.get().max_replicas.get();
            ret.autoscaling.get().min.get() = hpa.spec.get().min_replicas.get();
            ret.autoscaling.get().target.get() = hpa.spec.get().scale_target_ref.get().name.get();
        };
        helper.build<kube_api::horizontal_pod_autoscaler>()
            .read(arg.namespace_, arg.name)
            .response_switch()
            .response_case<200, kubeent::horizontal_pod_autoscaler>(autoscaling_cb);

        auto pod_cb = [&ret, &arg] (kubeent::pod_list & list) -> void
        {
            for (auto & pod : list.items.get().values()) {
                if (pod.metadata.get().labels.get().values().find("nava_app") == pod.metadata.get().labels.get().values().end()) {
                    continue;
                }
                if (pod.metadata.get().labels.get().values()["nava_app"].str.compare(arg.name) != 0) {
                    continue;
                }

                ret.pod.get().values().push_back(func_pod_list_item());

                ret.pod.get().values().back().name = std::string(pod.metadata.get().name.get());
                ret.pod.get().values().back().namespace_ = std::string(pod.metadata.get().namespace_.get());
                ret.pod.get().values().back().image = std::string(pod.status.get().container_statuses.get().values().front().image.get());
                ret.pod.get().values().back().node = std::string(pod.spec.get().node_name.get());
                ret.pod.get().values().back().policy = std::string(pod.spec.get().containers.get().values().back().image_pull_policy.get());
                ret.pod.get().values().back().status = std::string(pod.status.get().phase.get());
            }
        };
        helper.build<kube_api::pod>()
            .list(arg.namespace_)
            .response_switch()
            .response_case<200, kubeent::pod_list>(pod_cb);

        return ret;
    }
}

void func::func_repo_image_filter(std::map<std::string, std::list<std::string>> & stored,
                                  navagraha::dockerent::image & image)
{
    if (image.labels.get().values().find(std::string("navafunc")) != image.labels.get().values().end()) {
        std::string fullname = image.repo_tags.get().values().front();
        std::string::iterator tag_spliter = std::find(std::begin(fullname), std::end(fullname), ':');

        if (tag_spliter == std::end(fullname)) {
            if (stored.find(fullname) == std::end(stored)) {
                stored.insert(std::make_pair(fullname, std::list<std::string>()));
            }
        }
        else {
            std::string tag_name(std::begin(fullname), tag_spliter);
            tag_spliter++;
            std::string version(tag_spliter, std::end(fullname));
            if (stored.find(tag_name) == std::end(stored)) {
                stored.insert(std::make_pair(tag_name, std::list<std::string>()));
            }
            stored[tag_name].push_back(version);
        }
    }
}

char FUNC_REPO_ITEM_NAME[] = "name";
char FUNC_REPO_ITEM_VERSIONS[] = "versions";

void func_repo_item::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name)
        .add(this->versions);
}

char FUNC_LIST_ITEM_NAMESPACE[] = "namespace";
char FUNC_LIST_ITEM_NAME[] = "name";
char FUNC_LIST_ITEM_STATEFUL[] = "stateful";
char FUNC_LIST_ITEM_IMAGE_TAG[] = "imageTag";
char FUNC_LIST_ITEM_REPLICAS[] = "replicas";
char FUNC_LIST_ITEM_AVAILABLE[] = "available";
char FUNC_LIST_ITEM_UNAVAILABLE[] = "unavailable";

void func_list_item::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->namespace_)
        .add(this->name)
        .add(this->stateful)
        .add(this->image_tag)
        .add(this->replicas)
        .add(this->available)
        .add(this->unavailable);
}

char FUNC_POD_LIST_ITEM_NAMESPACE[] = "namespace";
char FUNC_POD_LIST_ITEM_NAME[] = "name";
char FUNC_POD_LIST_ITEM_STATUS[] = "status";
char FUNC_POD_LIST_ITEM_IMAGE[] = "imageTag";
char FUNC_POD_LIST_ITEM_POLICY[] = "policy";
char FUNC_POD_LIST_ITEM_NODE[] = "node";

void func_pod_list_item::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->namespace_)
        .add(this->name)
        .add(this->status)
        .add(this->image)
        .add(this->policy)
        .add(this->node);
}

char FUNC_AUTOSCALING_LIST_ITEM_NAME[] = "name";
char FUNC_AUTOSCALING_LIST_ITEM_CPU[] = "cpu";
char FUNC_AUTOSCALING_LIST_ITEM_MIN_REPLICAS[] = "minReplicas";
char FUNC_AUTOSCALING_LIST_ITEM_MAX_REPLICAS[] = "maxReplicas";
char FUNC_AUTOSCALING_LIST_ITEM_TARGET[] = "target";

void func_autoscaling_list_item::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->name)
        .add(this->cpu)
        .add(this->min)
        .add(this->max)
        .add(this->target);
}

char FUNC_DETAIL_COMMON[] = "common";
char FUNC_DETAIL_AUTOSCALING[] = "autoscaling";
char FUNC_DETAIL_PODS[] = "pods";


void func_detail::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->common)
        .add(this->autoscaling)
        .add(this->pod);
}

}
}
