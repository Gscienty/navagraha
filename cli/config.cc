#include "cli/config.hpp"

namespace navagraha {
namespace cli {

static config _instance;

config & config::get_instance()
{
    return _instance;
}

}
}
