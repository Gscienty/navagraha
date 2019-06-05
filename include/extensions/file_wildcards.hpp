#ifndef _NAVAGRAHA_EXTENSIONS_FILE_WILDCARDS_H
#define _NAVAGRAHA_EXTENSIONS_FILE_WILDCARDS_H

#include <string>

namespace navagraha {
namespace extensions {

class file_wildcards {
public:
    file_wildcards(std::string wildcard);

    bool match(const std::string & filename) const;
};

}
}

#endif
