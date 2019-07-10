#include "http_client/http_response.hpp"

namespace navagraha {
namespace http_client {

http_response::http_response(std::function<long (std::ostringstream &)> caller)
{
    std::ostringstream oss;
    this->response_code = caller(oss);
    this->result_str = oss.str();
}

http_response & http_response::response_switch()
{
    this->response_code_switch_case_hit = false;
    return *this;
}

}
}
