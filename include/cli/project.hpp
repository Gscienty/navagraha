#ifndef _NAVAGRAHA_CLI_PROJECT_H
#define _NAVAGRAHA_CLI_PROJECT_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/process_arg.hpp"

namespace navagraha {
namespace cli {

extern char CLI_PROJECT_FLAG[];

class project : public cli_arg::abstract_process<project> {
private:
    cli_arg::process_arg<CLI_PROJECT_FLAG> name_flag;
public:
    virtual void bind(cli_arg::process_helper<project> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
