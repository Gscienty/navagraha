#ifndef _NAVAGRAHA_ARG_arg_def_H
#define _NAVAGRAHA_ARG_arg_def_H

#include "args/arg.hpp"
#include <string>
#include <list>
#include <memory>

namespace navagraha {
namespace arg {

class def {
private:
    std::shared_ptr<arg> _ptr;
    void _put(const char * arg_name);
public:
    def(def & prerequired, const char * arg_name,
            size_t params_count = 0);
    def(const char * arg_name, size_t params_count = 0);
    std::shared_ptr<arg> & ptr();
    arg & argument();
    void pet(const char * arg_name);
    bool & used();
    std::vector<std::string> & params();
};

bool transfer(int argc, char ** argv);

}
}

#endif
