#include "cli/namespace_list.hpp"
#include "cli/config.hpp"
#include "kube_api/namespace.hpp"
#include <algorithm>
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_NAMESPACE_LIST_FLAG[] = "list";

void namespace_list::bind(cli_arg::process_helper<namespace_list> & helper)
{
    helper
        .add(this->list_flag);
}

bool namespace_list::satisfy() const
{
    return this->list_flag.used();
}

void namespace_list::display_item(kubeent::namespace_ & namespace_)
{
    std::cout << namespace_.metadata.get().name.get() << std::endl;
}

int namespace_list::execute()
{
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);

    kubeent::namespace_list namespaces = helper.build<kube_api::namespace_>().list();

    std::for_each(namespaces.items.get().values().begin(),
                  namespaces.items.get().values().end(),
                 std::bind(&namespace_list::display_item, this, std::placeholders::_1));

    return 0;
}

}
}
