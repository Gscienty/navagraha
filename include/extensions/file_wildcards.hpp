#ifndef _NAVAGRAHA_EXTENSIONS_FILE_WILDCARDS_H
#define _NAVAGRAHA_EXTENSIONS_FILE_WILDCARDS_H

#include <string>
#include <list>

namespace navagraha {
namespace extensions {

class file_wildcards {
private:
    bool is_file;
    bool exclude_rule;
    std::list<std::string> folder;
    std::string name;

public:
    file_wildcards(std::string wildcard);

    bool match(const std::string & filename, bool is_file) const;

    bool exclude() const;
};

}
}

#endif
