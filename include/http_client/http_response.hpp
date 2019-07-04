#ifndef _NAVAGRAHA_HTTP_CLIENT_HTTP_RESPONSE_H
#define _NAVAGRAHA_HTTP_CLIENT_HTTP_RESPONSE_H

#include <curl/curl.h>
#include <string>
#include <sstream>
#include <functional>
#include <cstddef>
#include <iostream>

namespace navagraha {
namespace http_client {

class http_response {
private:
    long response_code;
    std::ostringstream result_stream;
    std::function<void (std::string)> receive_cb;
    int result_status_code;
public:
    http_response(std::function<long (http_response &)> caller);

    void set_write_func(CURL * curl);

    size_t write(const char * ptr, size_t size);

    std::string result() const;

    template <typename T> T get()
    {
        return T::deserialize(this->result_stream.str());
    }
};

}
}

#endif
