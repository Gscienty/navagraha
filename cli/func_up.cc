#include "cli/func_up.hpp"
#include "cli/config.hpp"
#include "kubeent/deployment.hpp"
#include "kubeent/stateful_set.hpp"
#include "kubeent/service.hpp"
#include "kube_api/deployment.hpp"
#include "kube_api/service.hpp"
#include "kube_api/stateful_set.hpp"
#include <algorithm>
#include <cstdlib>

namespace navagraha {
namespace cli {

char CLI_FUNC_DEPLOY_NAME[] = "up";
char CLI_FUNC_DEPLOY_STATEFUL[] = "--stateful";
char CLI_FUNC_DEPLOY_POLICY[] = "--policy";
char CLI_FUNC_DEPLOY_IMAGE[] = "--image";
char CLI_FUNC_DEPLOY_NAMESPACE[] = "--namespace";
char CLI_FUNC_DEPLOY_CONFIG_VOLUME[] = "--config-volume";
char CLI_FUNC_DEPLOY_MIN_READY_SECONDS[] = "--ready-seconds";
char CLI_FUNC_DEPLOY_REPLICAS[] = "--replicas";
char CLI_FUNC_DEPLOY_UPDATE_FLAG[] = "--update";
char CLI_FUNC_DEPLOY_UPDATE_TYPE[] = "--update-type";
char CLI_FUNC_DEPLOY_UPDATE_SURGE[] = "--update-surge";
char CLI_FUNC_DEPLOY_UPDATE_UNAVAILABLE[] = "--update-unavailable";
char CLI_FUNC_DEPLOY_UPDATE_PARTITION[] = "--partition";

void func_up::bind(cli_arg::process_helper<func_up> & helper)
{
    this->stateful_arg.require(this->name_arg);
    this->policy_arg.require(this->name_arg);
    this->image_arg.require(this->name_arg);
    this->namespace_arg.require(this->name_arg);
    this->config_volume_arg.require(this->name_arg);
    this->min_ready_seconds_arg.require(this->name_arg);
    this->update_flag_arg.require(this->name_arg);
    this->update_type_arg.require(this->update_flag_arg);
    this->update_surge_arg.require(this->update_flag_arg);
    this->update_unavailable_arg.require(this->update_flag_arg);
    this->partition_arg.require(this->stateful_arg);
    this->replicas_arg.require(this->name_arg);

    helper
        .add(this->name_arg)
        .add(this->replicas_arg)
        .add(this->stateful_arg)
        .add(this->policy_arg)
        .add(this->image_arg)
        .add(this->config_volume_arg)
        .add(this->min_ready_seconds_arg)
        .add(this->update_flag_arg)
        .add(this->update_type_arg)
        .add(this->update_surge_arg)
        .add(this->update_unavailable_arg)
        .add(this->partition_arg);
}

bool func_up::satisfy() const 
{
    if (!this->name_arg.used()) {
        return false;
    }

    if (!this->image_arg.used()) {
        return false;
    }

    return true;
}

void func_up::create_deployment(std::string namespace_, http_client::curl_helper & helper)
{
    kubeent::deployment req_obj;

    req_obj.api_version = std::string("apps/v1");
    req_obj.kind = std::string("Deployment");
    req_obj.metadata.get().name = std::string(this->name_arg[0]);
    req_obj.metadata.get().labels.get().values()["nava_app"] = std::string(this->name_arg[0]);
    req_obj.spec.get().replicas = ::atoi(this->replicas_arg[0].c_str());
    req_obj.spec.get().selector.get().match_labels.get()
        .values()["nava_app"] = std::string(this->name_arg[0]);

    req_obj.spec.get().template_.get().metadata.get().labels.get()
        .values()["nava_app"] = std::string(this->name_arg[0]);
    req_obj.spec.get().template_.get().metadata.get().labels.get()
        .values()["common_domain"] = std::string("navagraha_func");
    req_obj.spec.get().template_.get().metadata.get().annotations.get()
        .values()["prometheus.io/path"] = std::string("/metrics");
    req_obj.spec.get().template_.get().metadata.get().annotations.get()
        .values()["prometheus.io/port"] = std::string("80");
    req_obj.spec.get().template_.get().metadata.get().annotations.get()
        .values()["prometheus.io/scrape"] = std::string("true");
    req_obj.spec.get().template_.get().spec.get().containers.get()
        .values().push_back(kubeent::container());
    req_obj.spec.get().template_.get().spec.get().containers.get()
        .values().front().name = std::string(this->name_arg[0]);
    req_obj.spec.get().template_.get().spec.get().containers.get()
        .values().front().image = std::string(this->image_arg[0]);
    req_obj.spec.get().template_.get().spec.get().containers.get().values().front().ports.get()
        .values().push_back(kubeent::container_port());
    req_obj.spec.get().template_.get().spec.get().containers.get().values().front().ports.get()
        .values().front().container_port_ = 80;
    req_obj.spec.get().template_.get().spec.get().containers.get().values().front().env.get()
        .values().push_back(kubeent::env_var());
    req_obj.spec.get().template_.get().spec.get().containers.get().values().front().env.get()
        .values().front().name = std::string("HUMHA_NAMESPACE");
    req_obj.spec.get().template_.get().spec.get().containers.get().values().front().env.get()
        .values().front().value = std::string(namespace_);

    if (this->policy_arg.used()) {
        req_obj.spec.get().template_.get().spec.get().containers.get().values().front()
            .image_pull_policy = std::string(this->policy_arg[0]);
    }

    if (this->config_volume_arg.used()) {
        auto eachor = [&req_obj] (const std::array<std::string, 3> & volume) -> void
        {
            req_obj.spec.get().template_.get().spec.get().volumes.get().values()
                .push_back(kubeent::volume());
            req_obj.spec.get().template_.get().spec.get().volumes.get().values()
                .back().name = std::string(volume[0]);
            req_obj.spec.get().template_.get().spec.get().volumes.get().values()
                .back().config_map.get().name = std::string(volume[1]);

            req_obj.spec.get().template_.get().spec.get().containers.get().values()
                .back().volume_mounts.get().values().push_back(kubeent::volume_mount());
            req_obj.spec.get().template_.get().spec.get().containers.get().values()
                .back().volume_mounts.get().values().back().name = std::string(volume[0]);
            req_obj.spec.get().template_.get().spec.get().containers.get().values()
                .back().volume_mounts.get().values().back().mount_path = std::string(volume[2]);
        };

        std::for_each(std::begin(this->config_volume_arg.get_params()),
                      std::end(this->config_volume_arg.get_params()),
                      eachor);
    }

    if (this->update_flag_arg.used()) {
        if (this->update_type_arg.used()) {
            req_obj.spec.get().strategy.get().type = std::string(this->update_type_arg[0]);
        }
        else {
            req_obj.spec.get().strategy.get().type = std::string("RollingUpdate");
        }
        if (this->update_surge_arg.used()) {
            req_obj.spec.get().strategy.get().rolling_update.get().max_surge = ::atoi(this->update_surge_arg[0].c_str());
        }
        if (this->update_unavailable_arg.used()) {
            req_obj.spec.get().strategy.get().rolling_update.get().max_unavailable = ::atoi(this->update_unavailable_arg[0].c_str());
        }

        helper.build<kube_api::deployment>().replace(namespace_, this->name_arg[0], req_obj);
    }
    else {
        helper.build<kube_api::deployment>().create(namespace_, req_obj);
    }
}

void func_up::create_stateful(std::string namespace_, http_client::curl_helper & helper)
{
    kubeent::stateful_set req_obj;

    req_obj.api_version = std::string("apps/v1");
    req_obj.kind = std::string("StatefulSet");
    req_obj.metadata.get().name = std::string(this->name_arg[0]);
    req_obj.metadata.get().labels.get().values()["nava_app"] = std::string(this->name_arg[0]);
    req_obj.spec.get().replicas = ::atoi(this->replicas_arg[0].c_str());
    req_obj.spec.get().selector.get().match_labels.get()
        .values()["nava_app"] = std::string(this->name_arg[0]);

    req_obj.spec.get().template_.get().metadata.get().labels.get()
        .values()["nava_app"] = std::string(this->name_arg[0]);
    req_obj.spec.get().template_.get().metadata.get().labels.get()
        .values()["common_domain"] = std::string("navagraha_func");
    req_obj.spec.get().template_.get().metadata.get().labels.get()
        .values()["prometheus.io/path"] = std::string("/metrics");
    req_obj.spec.get().template_.get().metadata.get().labels.get()
        .values()["prometheus.io/port"] = std::string("80");
    req_obj.spec.get().template_.get().metadata.get().labels.get()
        .values()["prometheus.io/scrape"] = std::string("true");
    req_obj.spec.get().template_.get().spec.get().containers.get()
        .values().push_back(kubeent::container());
    req_obj.spec.get().template_.get().spec.get().containers.get()
        .values().front().name = std::string(this->name_arg[0]);
    req_obj.spec.get().template_.get().spec.get().containers.get()
        .values().front().image = std::string(this->image_arg[0]);
    req_obj.spec.get().template_.get().spec.get().containers.get()
        .values().front().ports.get().values().push_back(kubeent::container_port());
    req_obj.spec.get().template_.get().spec.get().containers.get().values().front().ports.get()
        .values().front().container_port_ = 80;
    req_obj.spec.get().template_.get().spec.get().containers.get().values().front().env.get()
        .values().push_back(kubeent::env_var());
    req_obj.spec.get().template_.get().spec.get().containers.get().values().front().env.get()
        .values().front().name = std::string("HUMHA_NAMESPACE");
    req_obj.spec.get().template_.get().spec.get().containers.get().values().front().env.get()
        .values().front().value = std::string(namespace_);

    if (this->policy_arg.used()) {
        req_obj.spec.get().template_.get().spec.get().containers.get().values().front()
            .image_pull_policy = std::string(this->policy_arg[0]);
    }

    if (this->config_volume_arg.used()) {
        auto eachor = [&req_obj] (const std::array<std::string, 3> & volume) -> void
        {
            req_obj.spec.get().template_.get().spec.get().volumes.get().values()
                .push_back(kubeent::volume());
            req_obj.spec.get().template_.get().spec.get().volumes.get().values()
                .front().name = std::string(volume[0]);
            req_obj.spec.get().template_.get().spec.get().volumes.get().values()
                .front().config_map.get().name = std::string(volume[1]);

            req_obj.spec.get().template_.get().spec.get().containers.get().values()
                .front().volume_mounts.get().values().push_back(kubeent::volume_mount());
            req_obj.spec.get().template_.get().spec.get().containers.get().values()
                .front().volume_mounts.get().values().front().mount_path = std::string(volume[2]);
        };

        std::for_each(std::begin(this->config_volume_arg.get_params()),
                      std::end(this->config_volume_arg.get_params()),
                      eachor);
    }

    if (this->update_flag_arg.used()) {
        if (this->update_type_arg.used()) {
            req_obj.spec.get().update_strategy.get().type = std::string(this->update_type_arg[0]);
        }
        else {
            req_obj.spec.get().update_strategy.get().type = std::string("RollingUpdate");
        }
        if (this->partition_arg.used()) {
            req_obj.spec.get().update_strategy.get().rolling_update.get().partition = ::atoi(this->partition_arg[0].c_str());
        }
        helper.build<kube_api::stateful_set>().replace(namespace_, this->name_arg[0], req_obj);
    }
    else {
        helper.build<kube_api::stateful_set>().create(namespace_, req_obj);
    }
}

void func_up::create_service(std::string namespace_, http_client::curl_helper & helper)
{
    kubeent::service req_obj;

    req_obj.api_version = std::string("v1");
    req_obj.kind = std::string("Service");
    req_obj.metadata.get().name = std::string(this->name_arg[0]);
    req_obj.metadata.get().labels.get().values()["common_domain"] = std::string("navagraha_func_svc");
    req_obj.spec.get().selector.get().values()["nava_app"] = std::string(this->name_arg[0]);
    req_obj.spec.get().selector.get().values()["common_domain"] = std::string("navagraha_func");
    req_obj.spec.get().ports.get().values().push_back(kubeent::service_port());
    req_obj.spec.get().ports.get().values().front().port = 80;

    helper.build<kube_api::service>().create(namespace_, req_obj);
}

int func_up::execute()
{
    std::string namespace_ = "default";
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);
    if (this->namespace_arg.used()) {
        namespace_ = this->namespace_arg[0];
    }

    if (!this->stateful_arg.used()) {
        this->create_deployment(namespace_, helper);
    }
    this->create_service(namespace_, helper);
    if (this->stateful_arg.used()) {
        this->create_stateful(namespace_, helper);
    }
    
    return 0;
}


}
}
