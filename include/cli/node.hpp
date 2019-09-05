#ifndef _NAVAGRAHA_CLI_NODE_H
#define _NAVAGRAHA_CLI_NODE_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/process_arg.hpp"

namespace navagraha {
namespace cli {

extern char CLI_NODE_FLAG[];

class node : public cli_arg::abstract_process<node> {
private:
    cli_arg::process_arg<CLI_NODE_FLAG> name_flag;
public:
    virtual void bind(cli_arg::process_helper<node> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
