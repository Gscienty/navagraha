#ifndef _NAVAGRAHA_CLI_INVOKE_H
#define _NAVAGRAHA_CLI_INVOKE_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"

namespace navagraha {
namespace cli {

extern char CLI_INVOKE_NAME[];
extern char CLI_INVOKE_NAMESPACE[];
extern char CLI_INVOKE_PAYLOAD[];

class invoke : public cli_arg::abstract_process<invoke> {
private:
    cli_arg::arg<CLI_INVOKE_NAME, 1> invoke_name;
    cli_arg::arg<CLI_INVOKE_NAMESPACE, 1> namespace_arg;
    cli_arg::arg<CLI_INVOKE_PAYLOAD, 1> payload_arg;

public:
    virtual void bind(cli_arg::process_helper<invoke> & helper) override;
    virtual int execute() override;
    virtual bool satisfy() const override;
};

}
}

#endif
