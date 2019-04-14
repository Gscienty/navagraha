#ifndef _NAVAGRAHA_CLI_ARG_ARGS_COLLECTION_H
#define _NAVAGRAHA_CLI_ARG_ARGS_COLLECTION_H

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

    template <typename T_Arg> arg_wrapper(T_Arg & arg)
    {
        this->name = arg.name();
        this->params_remain = std::bind(&T_Arg::params_remain, &arg);
        this->params_append = std::bind(&T_Arg::params_append,
                                        &arg,
                                        std::placeholders::_1);
        this->prerequired = std::bind(&T_Arg::prerequired, &arg);
        this->use = std::bind(&T_Arg::use, &arg);
    }
};


}
}

#endif
