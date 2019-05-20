#ifndef _NAVAGRAHA_CLI_image_build_H
#define _NAVAGRAHA_CLI_image_build_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_FUNC_BUILD_BUILD[];
extern char CLI_FUNC_BUILD_TAG[];
extern char CLI_FUNC_BUILD_PATH[];

class func_build : public cli_arg::abstract_process<func_build> {
private:
    cli_arg::arg<CLI_FUNC_BUILD_BUILD, 1> build_arg;
    cli_arg::arg<CLI_FUNC_BUILD_PATH, 1> path_arg;

    void received_callback(std::string & msg);

public:
    virtual void bind(cli_arg::process_helper<func_build> & helper) override;
    virtual int execute() override;
    virtual bool satisfy() const override;
};

}
}

#endif
