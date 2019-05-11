#ifndef _NAVAGAHA_CLI_DEPLOY_H
#define _NAVAGAHA_CLI_DEPLOY_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"

namespace navagraha {
namespace cli {

extern char CLI_DEPLOY_NAME[];

class deploy : public cli_arg::abstract_process<deploy> {
private:
    cli_arg::arg<CLI_DEPLOY_NAME, 0> switched_flag;

public:
    virtual void bind(cli_arg::process_helper<deploy> & helper) override;
    virtual int execute() override;
    virtual bool satisfy() const override;

};

}
}

#endif
