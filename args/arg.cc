#include "arg/arg.hpp"
#include <boost/foreach.hpp>

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

std::vector<std::string> & arg::value()
{
    return this->_params.value();
}

void arg::set_satisfy(boost::function<bool (const arg &)> satisfy)
{
    this->_satisfy = satisfy;
}

bool arg::satisfy()
{
    if (this->_satisfy.empty() || this->_satisfy(*this)) {
        return true;
    }
    return false;
}

std::string arg::value(std::string key)
{
    if (this->_indices.find(key) == this->_indices.end()) {
        return "";
    }
    return this->_params.value()[this->_indices[key]];
}

bool arg::set_index(std::string key, size_t index)
{
    if (0 <= index && index < this->_params.required_count()) {
        return false;
    }
    this->_indices.insert(std::make_pair(key, index));
    return true;
}

void arg::add_other_name(std::string name)
{
    this->_other_name.insert(name);
}

bool arg::hit(const char * arg_name)
{
    bool hit_result = false;
    if (this->_name.compare(arg_name) == 0) {
        hit_result = true;
    }
    else {
        for (auto itr = this->_other_name.begin();
             itr != this->_other_name.end();
             itr++) {
            if (itr->compare(arg_name) == 0) {
                hit_result = true;
            }
        }
    }

    if (!hit_result) {
        return false;
    }
    if (this->_prerequired == nullptr) {
        return true;
    }

    return this->_prerequired->_used;
}

void arg::used()
{
    this->_used = true;
}

}
}
