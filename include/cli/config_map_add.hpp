#ifndef _NAVAGRAHA_CLI_CONFIG_MAP_ADD_H
#define _NAVAGRAHA_CLI_CONFIG_MAP_ADD_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "cli_arg/multi_arg.hpp"

namespace navagraha {
namespace cli {

extern char CLI_CONFIG_MAP_ADD_FLAG[];
extern char CLI_CONFIG_MAP_ADD_VALUE[];
extern char CLI_CONFIG_MAP_ADD_NAMESPACE[];

class config_map_add : public cli_arg::abstract_process<config_map_add> {
private:
    cli_arg::arg<CLI_CONFIG_MAP_ADD_FLAG, 1> name_arg;
    cli_arg::arg<CLI_CONFIG_MAP_ADD_NAMESPACE, 1> namespace_arg;
    cli_arg::multi_arg<CLI_CONFIG_MAP_ADD_VALUE, 2> value_arg;

    bool file_exist(const std::string & filename) const;
    std::string base64_filecontent(const std::string filename) const;
public:
    virtual void bind(cli_arg::process_helper<config_map_add> & helper) override;
    virtual int execute() override;
    virtual bool satisfy() const override;

};

}
}

#endif
