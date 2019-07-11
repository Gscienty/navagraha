#ifndef _NAVAGRAHA_CLI_PROJECT_USAGE_H
#define _NAVAGRAHA_CLI_PROJECT_USAGE_H

#include "cli_arg/abstract_default_process.hpp"

namespace navagraha {
namespace cli {

class project_usage : public cli_arg::abstract_default_process<project_usage> {
public:
    virtual int execute() override;
};

}
}

#endif
