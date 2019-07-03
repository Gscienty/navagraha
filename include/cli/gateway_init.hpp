#ifndef _NAVAGRAHA_CLI_GATEWAY_INIT_H
#define _NAVAGRAHA_CLI_GATEWAY_INIT_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_GATEWAY_INIT_FLAG[];

class gateway_init : public cli_arg::abstract_process<gateway_init> {
private:
    cli_arg::arg<CLI_GATEWAY_INIT_FLAG, 0> init_flag;

    void create_pod(std::string namespace_, http_client::curl_helper & helper);
public:
    virtual void bind(cli_arg::process_helper<gateway_init> & helper) override;
    virtual int execute() override;
    virtual bool satisfy() const override;
};

}
}

#endif
