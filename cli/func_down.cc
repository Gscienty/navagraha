#include "cli/func_down.hpp"
#include "cli/config.hpp"
#include "http_client/curl_helper.hpp"
#include "kube_api/deployment.hpp"
#include "kube_api/service.hpp"
#include "kubeent/delete_options.hpp"
#include "process/func.hpp"

namespace navagraha {
namespace cli {

char CLI_FUNC_OFFLINE_NAME[] = "down";
char CLI_FUNC_OFFLINE_NAMESPACE[] = "--namespace";
char CLI_FUNC_OFFLINE_STATEFUL[] = "--stateful";

void func_down::bind(cli_arg::process_helper<func_down> & helper) 
{
    this->namespace_arg.require(this->name_arg);
    this->stateful_arg.require(this->name_arg);
    helper
        .add(this->name_arg)
        .add(this->namespace_arg)
        .add(this->stateful_arg);
}

bool func_down::satisfy() const
{
    if (!this->name_arg.used()) {
        return false;
    }
    return true;
}

int func_down::execute()
{
    std::string namespace_ = "default";
    if (this->namespace_arg.used()) {
        namespace_ = this->namespace_arg[0];
    }
    process::func_down_arg arg;

    arg.name = this->name_arg[0];
    arg.namespace_ = namespace_;
    arg.stateful = this->stateful_arg.used();

    process::func(config::get_instance()).down(arg);

    return 0;
}

}
}
