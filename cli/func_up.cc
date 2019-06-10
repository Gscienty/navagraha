#include "cli/func_up.hpp"
#include "cli/config.hpp"
#include "kubeent/deployment.hpp"
#include "kubeent/service.hpp"
#include "kube_api/deployment.hpp"
#include "kube_api/service.hpp"
#include <algorithm>

namespace navagraha {
namespace cli {

char CLI_FUNC_DEPLOY_NAME[] = "up";
char CLI_FUNC_DEPLOY_POLICY[] = "--policy";
char CLI_FUNC_DEPLOY_IMAGE[] = "--image";
char CLI_FUNC_DEPLOY_NAMESPACE[] = "--namespace";
char CLI_FUNC_DEPLOY_CONFIG_VOLUME[] = "--config-volume";

void func_up::bind(cli_arg::process_helper<func_up> & helper)
{
    this->policy_arg.require(this->name_arg);
    this->image_arg.require(this->name_arg);
    this->namespace_arg.require(this->name_arg);
    this->config_volume_arg.require(this->name_arg);

    helper
        .add(this->name_arg)
        .add(this->policy_arg)
        .add(this->image_arg)
        .add(this->config_volume_arg);
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
    req_obj.metadata.get().labels.get().values()["app"] = std::string(this->name_arg[0]);
    req_obj.spec.get().replicas = 1;
    req_obj.spec.get().selector.get().match_labels.get()
        .values()["app"] = std::string(this->name_arg[0]);
    req_obj.spec.get().template_.get().metadata.get().labels.get()
        .values()["app"] = std::string(this->name_arg[0]);
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

    helper.build<kube_api::deployment>().create(namespace_, req_obj);
}

void func_up::create_service(std::string namespace_, http_client::curl_helper & helper)
{
    kubeent::service req_obj;

    req_obj.api_version = std::string("v1");
    req_obj.kind = std::string("Service");
    req_obj.metadata.get().name = std::string(this->name_arg[0]);
    req_obj.spec.get().selector.get().values()["app"] = std::string(this->name_arg[0]);
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

    this->create_deployment(namespace_, helper);
    this->create_service(namespace_, helper);
    
    return 0;
}


}
}
