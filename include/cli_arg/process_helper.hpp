#ifndef _NAVAGRAHA_CLI_ARG_PROCESS_HELPER_H
#define _NAVAGRAHA_CLI_ARG_PROCESS_HELPER_H

#include <list>
#include "cli_arg/arg_wrapper.hpp"

namespace navagraha {
namespace cli_arg {

template <typename T_Process> class process_helper {
private:
    T_Process process;
    std::list<arg_wrapper> args;
    int result_;

public:
    process_helper(T_Process & process)
        : process(process)
        , result_(0)
    {
        this->process.bind(*this);
    }

    template <typename T_Arg> process_helper & add(T_Arg & arg)
    {
        this->args.push_back(arg_wrapper(arg));
        return *this;
    }

    process_helper & bind(int argc, char ** argv)
    {
        for (int i = 1; i < argc; i++) {
            for (auto & arg : this->args) {
                if (arg.name.compare(std::string(argv[i])) == 0
                    && arg.prerequired()
                    && (arg.type == arg_type_process_arg
                        || argc - i >= arg.params_remain())) {
                    arg.begin();
                    if (arg.type == arg_type_common_arg) {
                        while (arg.params_remain() > 0) {
                            arg.params_append(argv[++i]);
                        }
                    }
                    else {
                        arg.set_args(argc - i, argv + i);
                    }
                    arg.use();
                    break;
                }
            }
        }
        return *this;
    }

    int result() const
    {
        return this->result_;
    }

    bool operator() ()
    {
        if (this->process.satisfy()) {
            this->result_ = this->process.execute();        
            return true;
        }
        return false;
    }
};

}
}

#endif
