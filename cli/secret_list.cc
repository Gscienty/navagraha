#include "cli/secret_list.hpp"
#include "cli/config.hpp"
#include "kubeent/secret_list.hpp"
#include "kube_api/secret.hpp"
#include <algorithm>
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_SECRET_LIST[] = "list";
char CLI_SECRET_LIST_NAMESPACE[] = "--namespace";

void secret_list::display_secret(kubeent::secret & sec)
{
    std::cout << sec.metadata.get().name.const_get() << std::endl;
}

void secret_list::bind(cli_arg::process_helper<secret_list> & helper)
{
    this->namespace_arg.require(this->list_arg);

    helper
        .add(this->list_arg)
        .add(this->namespace_arg);
}

bool secret_list::satisfy() const
{
    return this->list_arg.used();
}

int secret_list::execute()
{
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);
    std::string namespace_ = "default";
    if (this->namespace_arg.used()) {
        namespace_ = this->namespace_arg[0];
    }

    kubeent::secret_list secrets = helper.build<kube_api::secret>().list(namespace_);

    std::for_each(secrets.items.get().values().begin(),
                  secrets.items.get().values().end(),
                  std::bind(&secret_list::display_secret,
                            this,
                            std::placeholders::_1));

    return 0;
}

}
}
