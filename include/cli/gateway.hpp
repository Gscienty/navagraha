#ifndef _NAVAGRAHA_CLI_GATEWAY_H
#define _NAVAGRAHA_CLI_GATEWAY_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/process_arg.hpp"

namespace navagraha {
namespace cli {

extern char CLI_GATEWAY_FLAG[];

class gateway : public cli_arg::abstract_process<gateway> {
private:
    cli_arg::process_arg<CLI_GATEWAY_FLAG> name_flag;
public:
    virtual void bind(cli_arg::process_helper<gateway> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
