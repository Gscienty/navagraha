#ifndef _NAVAGRAHA_CLI_NAMESPACE_LIST_H
#define _NAVAGRAHA_CLI_NAMESPACE_LIST_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

class namespace_list : public cli_arg::abstract_process<namespace_list> {

};

}
}

#endif
