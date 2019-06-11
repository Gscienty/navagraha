#ifndef _NAVAGRAHA_CLI_MONITOR_INIT_H
#define _NAVAGRAHA_CLI_MONITOR_INIT_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_MONITOR_INIT_FLAG[];

class monitor_init : public cli_arg::abstract_process<monitor_init> {
private:
    cli_arg::arg<CLI_MONITOR_INIT_FLAG, 0> init_flag;

    void init_monitor_namespace(http_client::curl_helper & helper);
    void create_config_map(http_client::curl_helper & helper);
    void deployment_prometheus(http_client::curl_helper & helper);
    void create_rbac_service_account(http_client::curl_helper & helper);
public:
    virtual void bind(cli_arg::process_helper<monitor_init> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;

};

}
}

#endif
