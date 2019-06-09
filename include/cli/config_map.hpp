#ifndef _NAVAGRAHA_CLI_CONFIG_MAP_H
#define _NAVAGRAHA_CLI_CONFIG_MAP_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/process_arg.hpp"

namespace navagraha {
namespace cli {

extern char CLI_CONFIG_MAP_FLAG[];

class config_map : public cli_arg::abstract_process<config_map> {
private:
    cli_arg::process_arg<CLI_CONFIG_MAP_FLAG> name_flag;

public:
    virtual void bind(cli_arg::process_helper<config_map> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
