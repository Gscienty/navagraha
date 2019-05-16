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

client::client(CURL * curl, const std::string host)
    : curl(curl)
    , host(host)
    , binary_payload(NULL)
    , binary_payload_length(0)
{

}

client::~client()
{
    curl_easy_cleanup(this->curl);
}

std::string client::uri(const std::string path) const
{
    return this->host + path;
}

size_t client::write(const char * ptr, size_t size)
{
    this->result = std::string(ptr, size);
    return size;
}

std::string & client::curl_abstract_process(const std::string path, const char * method)
{
    curl_slist * headers = NULL;
    const std::string uri = this->uri(path);
    curl_easy_setopt(this->curl, CURLOPT_URL, uri.c_str());
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, __write_cb);
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, method);

    if (this->payload.size() != 0 || this->binary_payload_length != 0)
    {
        if (this->content_type.empty()) {
            headers = curl_slist_append(headers, "Content-Type: application/json; charset=UTF-8");
        }
        else {
            headers = curl_slist_append(headers, ("Content-Type: " + this->content_type).c_str());
        }
        curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, headers);
        if (this->payload.size() != 0) {
            curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, this->payload.c_str());
            curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, this->payload.size());
        }
        else {
            curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, this->binary_payload);
            curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, this->binary_payload_length);
        }
    }

    curl_easy_perform(this->curl);

    if (headers != NULL) {
        curl_slist_free_all(headers);
    }
    return this->result;
}

client & client::set_content_type(std::string content_type)
{
    this->content_type = content_type;
    return *this;
}

void client::set_binary_content(std::string & val)
{
    this->binary_payload = val.c_str();
    this->binary_payload_length = val.size();
}

}
}
