#ifndef _NAVAGRAHA_CLI_CONFIG_H
#define _NAVAGRAHA_CLI_CONFIG_H

#include <string>

namespace navagraha {
namespace cli {

class config {
public:
    std::string kube_cert;
    std::string kube_key;
    std::string kube_ca;
    std::string kube_api_server;

    static config & get_instance();
};

}
}

#endif
