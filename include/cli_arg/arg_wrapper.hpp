#ifndef _NAVAGRAHA_CLI_ARG_ARGS_COLLECTION_H
#define _NAVAGRAHA_CLI_ARG_ARGS_COLLECTION_H

#include "cli_arg/arg.hpp"
#include "cli_arg/process_arg.hpp"
#include "cli_arg/arg_type.hpp"
#include <string>
#include <functional>

namespace navagraha {
namespace cli_arg {

struct arg_wrapper {
    std::string name;
    std::function<int ()> params_remain;
    std::function<void (const char * const)> params_append;
    std::function<bool ()> prerequired;
    std::function<void ()> use;
    std::function<void (int, char **)> set_args;
    std::function<void ()> begin;
    arg_type type;

    template <typename T_Arg> arg_wrapper(T_Arg & arg)
    {
        this->name = arg.name();
        this->prerequired = std::bind(&T_Arg::prerequired, &arg);
        this->use = std::bind(&T_Arg::use, &arg);
        this->begin = std::bind(&T_Arg::begin, &arg);
        this->type = arg.type();
        if (this->type == arg_type_common_arg) {
            this->params_remain = std::bind(&T_Arg::params_remain, &arg);
            this->params_append = std::bind(&T_Arg::params_append,
                                            &arg,
                                            std::placeholders::_1);
        }
        else {
            this->set_args = std::bind(&T_Arg::set_args,
                                       &arg,
                                       std::placeholders::_1,
                                       std::placeholders::_2);
        }
    }
};


}
}

#endif
