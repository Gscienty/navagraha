#ifndef _NAVAGRAHA_CLI_FUNC_H
#define _NAVAGRAHA_CLI_FUNC_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/process_arg.hpp"

namespace navagraha {
namespace cli {

extern char CLI_FUNC_FLAG[];

class func : public cli_arg::abstract_process<func> {
private:
    cli_arg::process_arg<CLI_FUNC_FLAG> name_flag;
public:
    virtual void bind(cli_arg::process_helper<func> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
