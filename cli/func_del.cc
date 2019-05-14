#include "cli/func_del.hpp"
#include "cli/config.hpp"
#include "http_client/curl_helper.hpp"
#include "kube_api/deployment.hpp"
#include "kube_api/service.hpp"
#include "kubeent/delete_options.hpp"

namespace navagraha {
namespace cli {

char CLI_DEL_NAME[] = "del";
char CLI_DEL_NAMESPACE[] = "--namespace";


void func_del::bind(cli_arg::process_helper<func_del> & helper) 
{
    this->namespace_arg.require(this->name_arg);

    helper
        .add(this->name_arg)
        .add(this->namespace_arg);
}

bool func_del::satisfy() const
{
    if (!this->name_arg.used()) {
        return false;
    }

    return true;
}

int func_del::execute()
{
    std::string namespace_ = "default";
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);
    kubeent::delete_options deploy_del_ops;
    kubeent::delete_options service_del_ops;

    if (this->namespace_arg.used()) {
        namespace_ = this->namespace_arg[0];
    }

    helper.build<kube_api::deployment>().delete_(namespace_,
                                                 this->name_arg[0] + "-navagraha-deployment",
                                                 deploy_del_ops);
    helper.build<kube_api::service>().delete_(namespace_,
                                              this->name_arg[0] + "-navagraha-service",
                                              service_del_ops);


    return 0;
}

}
}
