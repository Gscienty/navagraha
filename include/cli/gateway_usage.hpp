#ifndef _NAVAGRAHA_CLI_GATEWAY_USAGE_H
#define _NAVAGRAHA_CLI_GATEWAY_USAGE_H

#include "cli_arg/abstract_default_process.hpp"

namespace navagraha {
namespace cli {

class gateway_usage : public cli_arg::abstract_default_process<gateway_usage> {
public:
    virtual int execute() override;
};

}
}

#endif
