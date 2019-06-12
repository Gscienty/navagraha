#ifndef _NAVAGRAHA_CLI_MONITOR_STOP_H
#define _NAVAGRAHA_CLI_MONITOR_STOP_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_MONITOR_STOP_FLAG[];

class monitor_stop : public cli_arg::abstract_process<monitor_stop> {
private:
    cli_arg::arg<CLI_MONITOR_STOP_FLAG, 0> break_flag;

    void delete_cluster_role(http_client::curl_helper & helper);
    void delete_namespace(http_client::curl_helper & helper);
public:
    virtual void bind(cli_arg::process_helper<monitor_stop> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;

};
}
}

#endif
