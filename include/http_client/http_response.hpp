#ifndef _NAVAGRAHA_HTTP_CLIENT_HTTP_RESPONSE_H
#define _NAVAGRAHA_HTTP_CLIENT_HTTP_RESPONSE_H

#include <curl/curl.h>
#include <string>
#include <sstream>
#include <functional>
#include <cstddef>
#include <iostream>
#include <map>

namespace navagraha {
namespace http_client {

class http_response {
private:
    long response_code;
    std::ostringstream result_stream;
    std::function<void (std::string)> receive_cb;
    int result_status_code;
    bool response_code_switch_case_hit;


public:
    http_response(std::function<long (http_response &)> caller);

    void set_write_func(CURL * curl);

    size_t write(const char * ptr, size_t size);

    std::string result() const;


    template<long T_Res_Code, typename T_Res_Obj> http_response & response_case(std::function<void (T_Res_Obj &)> func)
    {
        if (this->response_code_switch_case_hit == false && this->response_code == T_Res_Code) {
            T_Res_Obj obj = this->get<T_Res_Obj>();
            func(obj);
        }
        return *this;
    }

    http_response & response_switch();

    template <typename T> T get()
    {
        return T::deserialize(this->result_stream.str());
    }
};

}
}

#endif
