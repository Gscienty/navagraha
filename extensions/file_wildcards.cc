#include "extensions/file_wildcards.hpp"
#include <sstream>
#include <algorithm>

namespace navagraha {
namespace extensions {

file_wildcards::file_wildcards(std::string wildcard)
    : is_file(wildcard.back() != '/')
    , exclude_rule(wildcard.front() == '!')
{
    std::string f = this->exclude_rule
        ? std::string(wildcard.begin() + 1, wildcard.end())
        : wildcard;
    std::ostringstream str;
    auto eachor = [&str, this] (const char c) -> void
    {
        str.put(c);
        if (c == '/') {
            this->folder.push_back(std::string(str.str()));
            str.str("");
        }
    };
    std::for_each(std::begin(f), std::end(f), eachor);
    this->name = str.str();
}

bool file_wildcards::match(const std::string & filename, bool is_file) const
{
    if (this->is_file != is_file) {
        return false;
    }
    std::string f = filename;
    if (!is_file && f.back() != '/') {
        f += '/';
    }
    std::list<std::string> folder;
    std::ostringstream str;
    auto eachor = [& str, & folder] (const char c) -> void
    {
        str.put(c);
        if (c == '/') {
            folder.push_back(std::string(str.str()));
            str.str("");
        }
    };
    std::for_each(std::begin(f), std::end(f), eachor);
    std::string name = str.str();

    if (is_file) {
        if (this->folder.empty()) {
            
        }
        else {

        }
    }
    else {

    }

    return false;
}

bool file_wildcards::exclude() const
{
    return this->exclude_rule;
}

}
}
