#ifndef _NAVAGRAHA_CLI_MONITOR_H
#define _NAVAGRAHA_CLI_MONITOR_H

#include "cli_arg/abstract_process.hpp"

namespace navagraha {
namespace cli {

extern char CLI_MONITOR_FLAG[];

class monitor : public cli_arg::abstract_process<monitor> {
private:
    cli_arg::process_arg<CLI_MONITOR_FLAG> name_flag;

public:
    virtual void bind(cli_arg::process_helper<monitor> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
