#ifndef _NAVAGRAHA_CLI_ARG_ABSTRACT_DEFAULT_PROCESS_H
#define _NAVAGRAHA_CLI_ARG_ABSTRACT_DEFAULT_PROCESS_H

#include "cli_arg/abstract_process.hpp"

namespace navagraha {
namespace cli_arg {

template <typename T_Process>
class abstract_default_process : public abstract_process<T_Process> {
public:
    virtual bool satisfy() const override
    {
        return true;
    }

    virtual void bind(process_helper<T_Process> &) override
    {

    }
};

}
}

#endif
