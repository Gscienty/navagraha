#ifndef _NAVAGRAHA_CLI_MONITOR_TEST_START_H
#define _NAVAGRAHA_CLI_MONITOR_TEST_START_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_MONITOR_TEST_START_FLAG[];

class monitor_test_start : public cli_arg::abstract_process<monitor_test_start> {
private:
    cli_arg::arg<CLI_MONITOR_TEST_START_FLAG, 1> init_flag;

public:
    virtual void bind(cli_arg::process_helper<monitor_test_start> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;

};
}
}

#endif
