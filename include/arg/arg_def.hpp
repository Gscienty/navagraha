#ifndef _NAVAGRAHA_ARG_arg_def_H
#define _NAVAGRAHA_ARG_arg_def_H

#include "arg/arg.hpp"
#include <string>
#include <list>
#include <memory>

namespace navagraha {
namespace arg {

class arg_def {
private:
    std::shared_ptr<arg> _ptr;
    void _put(const char * arg_name);
public:

    arg_def(arg_def & prerequired, const char * arg_name,
            size_t params_count);
    arg_def(const char * arg_name, size_t params_count);
    std::shared_ptr<arg> & ptr();
    arg & argument();
};

bool transfer(int argc, char ** argv);

}
}

#endif
