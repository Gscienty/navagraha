#ifndef _NAVAGRAHA_CLI_MONITOR_BREAK_H
#define _NAVAGRAHA_CLI_MONITOR_BREAK_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_MONITOR_BREAK_FLAG[];

class monitor_break : public cli_arg::abstract_process<monitor_break> {
private:
    cli_arg::arg<CLI_MONITOR_BREAK_FLAG, 0> break_flag;

public:
    virtual void bind(cli_arg::process_helper<monitor_break> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;

};
}
}

#endif
