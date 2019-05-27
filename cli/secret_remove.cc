#include "cli/secret_remove.hpp"
#include "cli/config.hpp"
#include "kube_api/secret.hpp"

namespace navagraha {
namespace cli {

char CLI_SECRET_REMOVE[] = "remove";
char CLI_SECRET_REMOVE_NAMESPACE[] = "--namespace";

void secret_remove::bind(cli_arg::process_helper<secret_remove> & helper)
{
    this->namespace_arg.require(this->remove_arg);

    helper
        .add(this->remove_arg)
        .add(this->namespace_arg);
}

bool secret_remove::satisfy() const
{
    return this->remove_arg.used();
}

int secret_remove::execute()
{
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);
    std::string name = this->remove_arg[0];
    std::string namespace_ = "default";
    kubeent::delete_options opts;
    if (this->namespace_arg.used()) {
        namespace_ = this->namespace_arg[0];
    }

    helper.build<kube_api::secret>().delete_(namespace_, name, opts);

    return 0;
}

}
}
