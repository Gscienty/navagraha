#ifndef _NAVAGRAHA_HTTP_CLIENT_CLIENT_H
#define _NAVAGRAHA_HTTP_CLIENT_CLIENT_H

#include "http_client//http_response.hpp"
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <functional>

namespace navagraha {
namespace http_client {

class client {
private:
    CURL * curl;
    const std::string host;
    std::string payload;
    std::string content_type;
    const char * binary_payload;
    size_t binary_payload_length;
    std::function<void (std::string &)> receive_cb;

    std::string uri(const std::string path) const;

protected:
    void curl_abstract_process(const std::string path, const char * method, http_response & response);

    http_response && get_request(const std::string path);

    http_response && put_request(const std::string path);

    http_response && delete_request(const std::string path);

    http_response && post_request(const std::string path);

    http_response && patch_request(const std::string path);

    template <typename T> void set_payload(T && obj)
    {
        std::ostringstream str;
        obj.serialize(str);
        this->payload = str.str();
    }

    void set_binary_content(std::string & val);

public:
    client(CURL * curl, const std::string host);

    virtual ~client();

    client & set_content_type(std::string content_type);

    client & set_receive_cb(std::function<void (std::string &)> cb);
};

}
}

#endif
