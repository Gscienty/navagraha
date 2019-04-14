#include "cli_arg/process_collection.hpp"

namespace navagraha {
namespace cli_arg {

process_collection::process_collection(int argc, char ** argv)
    : hited(false)
    , ret(0)
    , argc(argc)
    , argv(argv)
{

}

process_collection & process_collection::default_process(std::function<int ()> default_)
{
    this->default_ = default_;
    return *this;
}

int process_collection::result()
{
    if (this->hited) {
        return this->ret;
    }

    if (bool(this->default_)) {
        return this->default_();
    }
    else {
        return 0;
    }
}

}
}
