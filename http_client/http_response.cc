#include "http_client/http_response.hpp"

namespace navagraha {
namespace http_client {

http_response::http_response()
{

}

http_response::~http_response()
{

}

http_response http_response::mono_call(std::function<long (std::ostringstream *)> caller)
{
    http_response resp;
    std::ostringstream oss;
    resp.response_code = caller(&oss);
    resp.result_str = oss.str();

    return resp;
}

http_response http_response::chunk_call(std::function<long ()> caller)
{
    http_response resp;
    resp.response_code = caller();
    return resp;
}

http_response & http_response::set_result(std::string str)
{
    this->result_str = str;

    return *this;
}


http_response & http_response::response_switch()
{
    this->response_code_switch_case_hit = false;
    return *this;
}

}
}
