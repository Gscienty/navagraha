#ifndef _NAVAGRAHA_HTTP_CLIENT_HTTP_RESPONSE_H
#define _NAVAGRAHA_HTTP_CLIENT_HTTP_RESPONSE_H

#include <curl/curl.h>
#include <string>
#include <sstream>
#include <functional>
#include <cstddef>
#include <map>
#include <iostream>
#include <condition_variable>

namespace navagraha {
namespace http_client {

class http_response {
private:
    long response_code;
    bool response_code_switch_case_hit;
    std::string result_str;

    std::function<void (std::string &)> chunk_cunsumer;

    http_response();
public:
    static http_response mono_call(std::function<long (std::ostringstream *)> caller);

    static http_response chunk_call(std::function<long ()> caller);

    virtual ~http_response();

    template<long T_Res_Code, typename T_Res_Obj> http_response & response_case(std::function<void (T_Res_Obj &)> func)
    {
        if (this->response_code_switch_case_hit == false && this->response_code == T_Res_Code) {
            this->response_code_switch_case_hit = true;
            T_Res_Obj obj = this->get<T_Res_Obj>();
            func(obj);
        }
        return *this;
    }

    http_response & set_result(std::string str);

    http_response & response_switch();

    template <typename T> T get()
    {
        return T::deserialize(this->result_str);
    }
};

}
}

#endif
