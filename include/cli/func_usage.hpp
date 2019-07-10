#ifndef _NAVAGRAHA_CLI_FUNC_USAGE_H
#define _NAVAGRAHA_CLI_FUNC_USAGE_H

#include "cli_arg/abstract_default_process.hpp"

namespace navagraha {
namespace cli {

class func_usage : public cli_arg::abstract_default_process<func_usage> {
public:
    virtual int execute() override;
};

}
}

#endif
