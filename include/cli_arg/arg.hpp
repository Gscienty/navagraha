#ifndef _NAVAGRAHA_CLI_ARG_ARG_H
#define _NAVAGRAHA_CLI_ARG_ARG_H

#include <array>
#include <string>
#include <functional>

namespace navagraha {
namespace cli_arg {

template <char * T_Arg_Name, int T_Arg_Params_Count = 0>
class arg {
private:
    int params_count_;
    std::array<std::string, T_Arg_Params_Count> params;
    std::function<bool ()> require_arg_used;
    bool used_;
public:
    arg()
        : params_count_(0)
        , used_(false)
    {

    }

    template <typename T_Prerequired> void require(T_Prerequired prerequired_arg)
    {
        this->require_arg_used = std::bind(&T_Prerequired::used, &prerequired_arg);
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

    void params_append(const char * const param)
    {
        this->params[this->params_count_++] = std::string(param);
    }

    int params_remain() const
    {
        return T_Arg_Params_Count - this->params_count_;
    }

    std::string name() const
    {
        return std::string(T_Arg_Name);
    }

    void use()
    {
        this->used_ = true;
    }
};

}
}

#endif
