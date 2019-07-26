#ifndef _NAVAGRAHA_CLI_FUNC_AUTOSCALING_H
#define _NAVAGRAHA_CLI_FUNC_AUTOSCALING_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_FUNC_AUTOSCALING_NAME[];
extern char CLI_FUNC_AUTOSCALING_NAMESPACE[];
extern char CLI_FUNC_AUTOSCALING_CPU[];
extern char CLI_FUNC_AUTOSCALING_MIN[];
extern char CLI_FUNC_AUTOSCALING_MAX[];

class func_autoscaling : public cli_arg::abstract_process<func_autoscaling> {
private:
    cli_arg::arg<CLI_FUNC_AUTOSCALING_NAME, 1> name_arg;
    cli_arg::arg<CLI_FUNC_AUTOSCALING_NAMESPACE, 1> namespace_arg;
    cli_arg::arg<CLI_FUNC_AUTOSCALING_CPU, 1> cpu_arg;
    cli_arg::arg<CLI_FUNC_AUTOSCALING_MIN, 1> min_arg;
    cli_arg::arg<CLI_FUNC_AUTOSCALING_MAX, 1> max_arg;

public:
    virtual void bind(cli_arg::process_helper<func_autoscaling> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
