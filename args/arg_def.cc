#include "arg/arg_def.hpp"
#include <functional>
#include <map>

#include <iostream>

namespace navagraha {
namespace arg {

static std::map<std::string,
    std::list<std::shared_ptr<arg>>> __arguments;

static std::shared_ptr<arg>
__foreach(const std::string name, std::function<bool (arg &)> eachor)
{
    auto same_name_args_itr = __arguments.find(name);

    if (same_name_args_itr == __arguments.end()) {
        return nullptr;
    }

    for (auto arg_itr = same_name_args_itr->second.begin();
         arg_itr != same_name_args_itr->second.end();
         arg_itr++) {
        if (eachor(**arg_itr)) {
            return *arg_itr;
        }
    }

    return nullptr;
}

arg_def::arg_def(arg_def & prerequired, const char * arg_name,
                 size_t params_count)
{
    this->_ptr = std::make_shared<arg>(prerequired.ptr()->pointer(),
                                       arg_name,
                                       params_count);
    this->_put(arg_name);
}

arg_def::arg_def(const char * arg_name, size_t params_count)
{
    this->_ptr = std::make_shared<arg>(arg_name, params_count);
    this->_put(arg_name);
}


void arg_def::_put(const char * arg_name)
{
    if (__arguments.find(arg_name)
        == __arguments.end()) {
        __arguments
            .insert(std::make_pair(std::string(arg_name),
                                   std::list<std::shared_ptr<arg>>()));
    }
    __arguments[arg_name].push_back(this->_ptr);
}


std::shared_ptr<arg> & arg_def::ptr()
{
    return this->_ptr;
}

arg & arg_def::argument()
{
    return *this->_ptr;
}

bool transfer(int argc, char ** argv)
{
    std::shared_ptr<arg> narg = nullptr;

    for (int i = 1; i < argc; i++) {
        narg = __foreach(argv[i],
                         [&] (arg & narg) -> bool
                         {
                             return narg.hit();
                         });
        if (narg == nullptr) {
            return false;
        }
        while (narg->remain_param_count() != 0 && i + 1 < argc) {
            narg->append_param(argv[++i]);
        }
        if (narg->remain_param_count() != 0) {
            return false;
        }
        narg->used() = true;
    }

    return true;
}

}
}
