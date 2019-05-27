#include "cli/secret_add.hpp"
#include "cli/config.hpp"
#include "kubeent/secret.hpp"
#include "kube_api/secret.hpp"
#include <algorithm>

#include <iostream>

namespace navagraha {
namespace cli {

char CLI_SECRET_ADD[] = "add";
char CLI_SECRET_ADD_NAMESPACE[] = "--namespace";
char CLI_SECRET_ADD_VALUE[] = "--value";

void secret_add::bind(cli_arg::process_helper<secret_add> & helper)
{
    this->namespace_arg.require(this->add_arg);
    this->value_arg.require(this->add_arg);

    helper
        .add(this->add_arg)
        .add(this->value_arg)
        .add(this->namespace_arg);
}

bool secret_add::satisfy() const
{
    return this->add_arg.used();
}

int secret_add::execute()
{
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);
    
    std::string namespace_ = "default";
    if (this->namespace_arg.used()) {
        namespace_ = this->namespace_arg[0];
    }

    kubeent::secret secret;

    secret.api_version = std::string("v1");
    secret.kind = std::string("Secret");
    secret.type = std::string("Opaque");
    secret.metadata.get().name = std::string(this->add_arg[0]);

    std::for_each(this->value_arg.get_params().begin(),
                  this->value_arg.get_params().end(),
                  [&] (std::array<std::string, 2> & kv)
                  {
                  secret.string_data.get().values()[kv[0]] = kv[1];
                  });

    std::ostringstream str;
    secret.serialize(str);
    std::cout << str.str() << std::endl;

    helper.build<kube_api::secret>().create(namespace_, secret);

    return 0;
}

}
}
