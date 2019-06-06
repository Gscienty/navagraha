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

bool file_wildcards::item_match(const std::string & wild, const std::string & item) const
{
    std::string::const_iterator wild_last_common_itr = std::end(wild);
    std::string::const_iterator wild_iter = std::begin(wild);
    std::string::const_iterator iter;

    for (iter = std::begin(item);
         iter != std::end(item);
         iter++) {
        if (wild_iter == std::end(wild)) {
            if (wild_last_common_itr == std::end(wild)) {
                return false;
            }
            else {
                wild_iter = wild_last_common_itr;
            }
        }
        switch (*wild_iter) {
        case '*':
            wild_last_common_itr = wild_iter;
            wild_iter++;
            break;
        case '?':
            wild_iter++;
            break;
        default:
            if (*wild_iter == *iter) {
                wild_iter++;
            }
            else if (wild_last_common_itr != std::end(wild)) {
                wild_iter = wild_last_common_itr + 1;
            }
            else {
                return false;
            }
        }
    }

    return wild_iter == std::end(wild) && iter == std::end(item);
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

    std::list<std::string>::const_iterator wild_last_folder_common_itr
        = std::end(this->folder);
    std::list<std::string>::const_iterator wild_iter = std::begin(this->folder);
    std::list<std::string>::const_iterator iter;

    for (iter = std::begin(folder);
         iter != std::end(folder);
         iter++) {
        if (wild_iter == std::end(this->folder)) {
            if (!this->is_file) {
                return true;
            }
            else if (wild_last_folder_common_itr != std::end(this->folder)) {
                wild_iter = wild_last_folder_common_itr;
            }
            else {
                iter++;
                while (wild_iter != std::begin(this->folder)) {
                    wild_iter--;
                    iter--;
                }
            }
        }

        if (wild_iter->compare("**/") == 0) {
            wild_last_folder_common_itr = wild_iter;
            wild_iter++;
        }
        else if (this->item_match(*wild_iter, *iter)) {
            wild_iter++;
        }
        else if (wild_last_folder_common_itr != std::end(this->folder)) {
            wild_iter = wild_last_folder_common_itr;
            wild_iter++;
        }
        else {
            if (wild_iter != std::begin(this->folder)) {
                iter--;
            }
            wild_iter = std::begin(this->folder);
        }
    }

    if (this->is_file) { 
        return this->item_match(this->name, name);
    }
    else {
        return wild_iter == std::end(this->folder);
    }
}

bool file_wildcards::exclude() const
{
    return this->exclude_rule;
}

}
}
