#include "args/arg.hpp"

namespace navagraha {
namespace arg {

arg::arg(const arg * prerequired, const std::string name,
         const size_t params_count)
    : _prerequired(prerequired)
    , _name(name)
    , _params(params_count)
    , _used(false)
{

}

arg::arg(const std::string name, const size_t params_count)
    : _prerequired(nullptr)
    , _name(name)
    , _params(params_count)
    , _used(false)
{

}

bool arg::append_param(const char * param)
{
    return this->_params.append(param);
}

size_t arg::remain_param_count() const
{
    return this->_params.required_count()
        - this->_params.used_count();
}

std::vector<std::string> & arg::values()
{
    return this->_params.values();
}

std::string arg::value(std::string key)
{
    if (this->_indices.find(key) == this->_indices.end()) {
        return "";
    }
    return this->_params.values()[this->_indices[key]];
}

bool arg::set_index(std::string key, size_t index)
{
    if (0 <= index && index < this->_params.required_count()) {
        return false;
    }
    this->_indices.insert(std::make_pair(key, index));
    return true;
}

bool arg::hit()
{
    if (this->_prerequired == nullptr) {
        return true;
    }

    return this->_prerequired->_used;
}

bool & arg::used()
{
    return this->_used;
}

arg * arg::pointer()
{
    return this;
}

}
}
