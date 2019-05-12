#include "cli/deploy.hpp"
#include "kubeent/deployment.hpp"
#include "kube_api/deployment.hpp"
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_DEPLOY_NAME[] = "deploy";
char CLI_DEPLOY_POLICY[] = "--policy";
char CLI_DEPLOY_IMAGE[] = "--image";

void deploy::bind(cli_arg::process_helper<deploy> & helper)
{
    this->policy_arg.require(this->name_arg);
    this->image_arg.require(this->name_arg);

    helper
        .add(this->name_arg)
        .add(this->policy_arg)
        .add(this->image_arg);
}

bool deploy::satisfy() const 
{
    if (!this->name_arg.used()) {
        return false;
    }

    if (!this->image_arg.used()) {
        return false;
    }

    return true;
}

void deploy::create_deployment()
{
    kubeent::deployment req_obj;

    req_obj.api_version = std::string("apps/v1");
    req_obj.kind = std::string("Deployment");
    req_obj.metadata.get().name = std::string(this->name_arg[0]) + "-navagraha-deployment";
    req_obj.metadata.get()
        .labels.get()
        .values()["app"] = std::string(this->name_arg[0]);
    req_obj.spec.get().replicas = 1;
    req_obj.spec.get()
        .selector.get()
        .match_labels.get().values()["app"] = std::string(this->name_arg[0]);
    req_obj.spec.get()
        .template_.get()
        .metadata.get()
        .labels.get().values()["app"] = std::string(this->name_arg[0]);
    req_obj.spec.get()
        .template_.get()
        .spec.get()
        .containers.get().values().push_back(kubeent::container());
    req_obj.spec.get()
        .template_.get()
        .spec.get()
        .containers.get().values().front().name = std::string(this->name_arg[0]);
    req_obj.spec.get()
        .template_.get()
        .spec.get()
        .containers.get().values().front().image = std::string(this->image_arg[0]);
    req_obj.spec.get()
        .template_.get()
        .spec.get()
        .containers.get().values().front()
        .ports.get().values().push_back(kubeent::container_port());
    req_obj.spec.get()
        .template_.get()
        .spec.get()
        .containers.get().values().front()
        .ports.get().values().front().container_port_ = 80;

    std::ostringstream str;
    req_obj.serialize(str);

    std::cout << str.str() << std::endl;
}

int deploy::execute()
{
    this->create_deployment();
    
    return 0;
}


}
}
