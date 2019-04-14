#ifndef _NAVAGRAHA_CLI_ARG_ABSTRACT_PROCESS_H
#define _NAVAGRAHA_CLI_ARG_ABSTRACT_PROCESS_H

#include "cli_arg/process_helper.hpp"

namespace navagraha {
namespace cli_arg {

template <typename T_Process>
class abstract_process {
public:
    virtual void bind(process_helper<T_Process> & helper) = 0;
    virtual int execute() = 0;
    virtual bool satisfy() const = 0;
};

}
}

#endif
