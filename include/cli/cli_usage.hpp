#ifndef _NAVAGRAHA_CLI_CLI_USAGE_H
#define _NAVAGRAHA_CLI_CLI_USAGE_H

#include "cli_arg/abstract_default_process.hpp"

namespace navagraha {
namespace cli {

class cli_usage : public cli_arg::abstract_default_process<cli_usage> {
public:
    virtual int execute() override;
};

}
}

#endif
