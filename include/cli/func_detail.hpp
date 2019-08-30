#ifndef _NAVAGRAHA_CLI_FUNC_DETAIL_H
#define _NAVAGRAHA_CLI_FUNC_DETAIL_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "cli_arg/process_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_FUNC_DETAIL_NAME[];
extern char CLI_FUNC_DETAIL_NAMESPACE[];
extern char CLI_FUNC_DETAIL_STATEFUL[];

class func_detail : public cli_arg::abstract_process<func_detail> {
private:
    cli_arg::arg<CLI_FUNC_DETAIL_NAME, 1> name_arg;
    cli_arg::arg<CLI_FUNC_DETAIL_NAMESPACE, 1> namespace_arg;
    cli_arg::arg<CLI_FUNC_DETAIL_STATEFUL, 0> stateful_arg;

public:
    virtual void bind(cli_arg::process_helper<func_detail> & helper) override;
    virtual int execute() override;
    virtual bool satisfy() const override;
};

}
}

#endif
