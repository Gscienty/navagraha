#ifndef _NAVAGRAHA_CLI_ARG_PROCESS_ARG_H
#define _NAVAGRAHA_CLI_ARG_PROCESS_ARG_H

#include "cli_arg/arg_type.hpp"
#include <limits>
#include <functional>

namespace navagraha {
namespace cli_arg {

template <char * T_Arg_Name> class process_arg {
private:
    int argc_;
    char ** argv_;
    std::function<bool ()> require_arg_used;
    bool used_;

public:
    process_arg()
        : argc_(0)
        , argv_(nullptr)
        , used_(false)
    {

    }

    int argc() const
    {
        return this->argc_;
    }

    char ** argv() const
    {
        return this->argv_;
    }

    bool used() const
    {
        return this->used_;
    }

    bool prerequired() const
    {
        if (bool(this->require_arg_used) == false) {
            return true;
        }
        return this->require_arg_used();
    }

    std::string name() const
    {
        return std::string(T_Arg_Name);
    }

    arg_type type() const
    {
        return arg_type_process_arg;
    }

    void use()
    {
        this->used_ = true;
    }

    template <typename T_Prerequired> void require(T_Prerequired & prerequired_arg)
    {
        this->require_arg_used = std::bind(&T_Prerequired::used, &prerequired_arg);
    }

    void set_args(int argc, char ** argv)
    {
        this->argc_ = argc;
        this->argv_ = argv;
    }

    void params_append(const char * const)
    {

    }

    int params_remain() const
    {
        return std::numeric_limits<int>::max();
    }

    void begin()
    {

    }
};

}
}

#endif
