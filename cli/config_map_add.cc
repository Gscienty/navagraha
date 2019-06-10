#include "cli/config_map_add.hpp"
#include "cli/config.hpp"
#include "http_client/curl_helper.hpp"
#include "kubeent/config_map.hpp"
#include "kube_api/config_map.hpp"
#include "extensions/base64.hpp"
#include <unistd.h>
#include <algorithm>
#include <fstream>

namespace navagraha {
namespace cli {

char CLI_CONFIG_MAP_ADD_FLAG[] = "add";
char CLI_CONFIG_MAP_ADD_VALUE[] = "--value";
char CLI_CONFIG_MAP_ADD_NAMESPACE[] = "--namespace";

void config_map_add::bind(cli_arg::process_helper<config_map_add> & helper)
{
    this->value_arg.require(this->name_arg);
    this->namespace_arg.require(this->namespace_arg);

    helper
        .add(this->name_arg)
        .add(this->value_arg)
        .add(this->namespace_arg);
}

bool config_map_add::satisfy() const
{
    return this->name_arg.used();
}

int config_map_add::execute()
{
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);

    std::string namespace_ = "default";
    kubeent::config_map cm;

    if (this->namespace_arg.used()) {
        namespace_ = this->namespace_arg[0];
    }

    cm.api_version = std::string("v1");
    cm.kind = std::string("ConfigMap");
    cm.metadata.get().name = std::string(this->name_arg[0]);
    cm.metadata.get().labels.get().values()["name"] = std::string(this->name_arg[0]);

    auto eachor = [&cm, this] (const std::array<std::string, 2> val)
    {
        if (this->file_exist(val[1])) {
            cm.data.get().values()[std::string(val[0])]
                = this->base64_filecontent(val[1]);
        }
    };

    std::for_each(std::begin(this->value_arg.get_params()),
                  std::end(this->value_arg.get_params()),
                  eachor);

    helper.build<kube_api::config_map>().create(namespace_, cm);
    
    return 0;
}

bool config_map_add::file_exist(const std::string & filename) const
{
    return access(filename.c_str(), F_OK) == 0;
}

std::string config_map_add::base64_filecontent(const std::string filename) const
{
    std::filebuf fb;
    fb.open(filename.c_str(), std::ios::binary | std::ios::in);
    std::istream fs(&fb);
    std::ostringstream str;
    char c;
    while (fs.read(&c, 1)) {
        switch (c) {
        case '\n':
            str.put('\\');
            str.put('n');
            break;
        case '"':
            str.put('\\');
            str.put('"');
            break;
        case '\\':
            str.put('\\');
            str.put('\\');
            break;

        default:
            str.put(c);
        }
    }
    fb.close();
    return (str.str());
}

}
}
