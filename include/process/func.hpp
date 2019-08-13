#ifndef _NAVAGRAHA_PROCESS_FUNC_H
#define _NAVAGRAHA_PROCESS_FUNC_H

#include "cli/config.hpp"
#include "args/func_up.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace process {

class func {
private:
    cli::config & config;

    void func_up_create_deployment(http_client::curl_helper & helper,
                                   const args::func_up & func_up);
    void func_up_create_service(http_client::curl_helper & helper,
                                const args::func_up & func_up);
public:
    func(cli::config & cfg);

    std::string up(const args::func_up & func_up);
};

}
}

#endif
