#ifndef _NAVAGRAHA_CONFIG_MAP_H
#define _NAVAGRAHA_CONFIG_MAP_H

#include "cli/config.hpp"

namespace navagraha {
namespace process {

class config_map {
private:
    cli::config config;

public:
    config_map(cli::config & config);
};

}
}

#endif
