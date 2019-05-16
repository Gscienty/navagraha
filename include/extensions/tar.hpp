#ifndef _NAVAGRAHA_EXTENSIONS_TAR_H
#define _NAVAGRAHA_EXTENSIONS_TAR_H

#include <tar.h>
#include <libtar.h>
#include <string>

namespace navagraha {
namespace extensions {

class tar {
private:
    TAR * tar_handler;
    std::string tar_name;
    std::string dir;

    void direct_each(std::string direct_name);
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
