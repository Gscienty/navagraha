#include "http_client/http_response.hpp"

#include <iostream>

namespace navagraha {
namespace http_client {

static size_t __write_cb(void * ptr, size_t size, size_t nitems, void * stream)
{
    http_response * c = reinterpret_cast<http_response *>(stream);
    size_t readed_len = size;
    if (readed_len < size * nitems) {
        readed_len = size * nitems;
    }
    return c->write(reinterpret_cast<const char *>(ptr), readed_len);
}

http_response::http_response(std::function<long (http_response &)> caller)
{
    this->response_code = caller(*this);
}

size_t http_response::write(const char * ptr, size_t size)
{
    this->result_stream.write(ptr, size);
    if (this->receive_cb) {
        this->receive_cb(std::string(ptr, ptr + size));
    }
    return size;
}

std::string http_response::result() const
{
    return this->result_stream.str();
}

void http_response::set_write_func(CURL * curl)
{
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, __write_cb);
}


}
}
