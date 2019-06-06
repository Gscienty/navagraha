#ifndef _NAVAGRAHA_EXTENSIONS_TAR_H
#define _NAVAGRAHA_EXTENSIONS_TAR_H

#include "extensions/file_wildcards.hpp"
#include <tar.h>
#include <libtar.h>
#include <string>
#include <list>

namespace navagraha {
namespace extensions {

class tar {
private:
    TAR * tar_handler;
    std::string tar_name;
    std::string dir;
    const std::string ignore_filename;
    std::list<file_wildcards> ignored;

    void fill_ignored();
    bool ignore(const std::string & filename, bool is_file);
    void direct_each(std::string real_direct_name, std::string logic_direct_name);
public:
    tar(std::string tar_name, std::string dir);
    virtual ~tar();

    void operator() ();

    size_t size() const;

    void extract(std::string & str);
};

}
}

#endif
