#include "arg/arg_map.hpp"

namespace navagraha {
namespace arg {
arg_map::arg_map(std::shared_ptr<arg> & prerequired, const char * arg_name,
                 size_t params_count)
{
    this->_ptr = std::make_shared<arg>(prerequired->pointer(),
                                       arg_name,
                                       params_count);
    this->_put_arg_map(arg_name);
}

arg_map::arg_map(const char * arg_name, size_t params_count)
{
    this->_ptr = std::make_shared<arg>(arg_name, params_count);
    this->_put_arg_map(arg_name);
}

void arg_map::_put_arg_map(const char * arg_name)
{
    if (this->_arg_map.find(arg_name) == this->_arg_map.end()) {
        this->_arg_map
            .insert(std::make_pair(std::string(arg_name),
                                   std::list<std::shared_ptr<arg>>()));
    }
    this->_arg_map[arg_name].push_back(this->_ptr);
}

std::shared_ptr<arg> & arg_map::ptr()
{
    return this->_ptr;
}

}
}
