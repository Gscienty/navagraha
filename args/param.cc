#include "arg/param.hpp"

namespace navagraha {
namespace arg {

param::param(const size_t param_count)
    : _params_count(param_count)
    , _used_count(0)
{
    this->_params.resize(this->_params_count);
}

size_t param::required_count() const
{
    return this->_params_count;
}

size_t param::used_count() const
{
    return this->_used_count;
}

bool param::append(const char * param)
{

    if (this->used_count() >= this->required_count()) {
        return false;    
    }
    this->_params[this->_used_count++] = std::string(param);
    return true;
}

std::vector<std::string> & param::value()
{
    return this->_params;
}

}
}
