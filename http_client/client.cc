#include "http_client/client.hpp"

#include <iostream>

namespace navagraha {
namespace http_client {

static size_t __write_cb(void * ptr, size_t size, size_t nitems, void * stream)
{
    client * c = reinterpret_cast<client *>(stream);
    size_t readed_len = size;
    if (readed_len < size * nitems) {
        readed_len = size * nitems;
    }
    return c->write(reinterpret_cast<const char *>(ptr), readed_len);
}

client::client(CURL * curl, const std::string base_uri)
    : curl(curl)
    , base_uri(base_uri)
{

}

client::~client()
{
    curl_easy_cleanup(this->curl);
}

std::string client::uri(const std::string path) const
{
    return this->base_uri + path;
}

size_t client::write(const char * ptr, size_t size)
{
    this->result = std::string(ptr, size);
    return size;
}

std::string & client::curl_abstract_process(const std::string path, CURLoption option)
{
    const std::string uri = this->uri(path);
    curl_easy_setopt(this->curl, CURLOPT_URL, uri.c_str());
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, __write_cb);
    curl_easy_setopt(this->curl, option, 1L);

    curl_easy_perform(this->curl);

    return this->result;
}

std::string & client::curl_abstract_process(const std::string path, const char * method)
{
    const std::string uri = this->uri(path);
    curl_easy_setopt(this->curl, CURLOPT_URL, uri.c_str());
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, __write_cb);
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, method);

    curl_easy_perform(this->curl);

    return this->result;
}

std::string & client::get_call(const std::string path)
{
    return this->curl_abstract_process(path, CURLOPT_HTTPGET);
}

std::string & client::put_call(const std::string path)
{
    return this->curl_abstract_process(path, CURLOPT_PUT);
}

std::string & client::delete_call(const std::string path)
{
    return this->curl_abstract_process(path, "DELETE");
}

std::string & client::post_call(const std::string path)
{
    return this->curl_abstract_process(path, CURLOPT_POST);
}

std::string & client::patch_call(const std::string path)
{
    return this->curl_abstract_process(path, "PATCH");
}

}
}
