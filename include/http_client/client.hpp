#ifndef _NAVAGRAHA_HTTP_CLIENT_CLIENT_H
#define _NAVAGRAHA_HTTP_CLIENT_CLIENT_H

#include <curl/curl.h>
#include <sstream>
#include <string>

namespace navagraha {
namespace http_client {

class client {
private:
    CURL * curl;
    const std::string host;
    std::string result;

    std::string uri(const std::string path) const;

    std::string & curl_abstract_process(const std::string path, CURLoption option);
    std::string & curl_abstract_process(const std::string path, const char * method);

protected:
    template <typename T> T get_call(const std::string path)
    {
        return T::deserialize(this->curl_abstract_process(path, "GET"));
    }

    template <typename T> T put_call(const std::string path)
    {
        return T::deserialize(this->curl_abstract_process(path, "PUT"));
    }

    template <typename T> T delete_call(const std::string path)
    {
        return T::deserialize(this->curl_abstract_process(path, "DELETE"));
    }

    template <typename T> T post_call(const std::string path)
    {
        return T::deserialize(this->curl_abstract_process(path, "POST"));
    }

    template <typename T> T patch_call(const std::string path)
    {
        return T::deserialize(this->curl_abstract_process(path, "PATCH"));
    }

public:
    client(CURL * curl, const std::string host);

    virtual ~client();

    size_t write(const char * ptr, size_t size);
};

}
}

#endif
