#ifndef _NAVAGRAHA_EXTENSIONS_BASE64_H
#define _NAVAGRAHA_EXTENSIONS_BASE64_H

#include <string>

namespace navagraha {
namespace extensions {

std::string base64_encode(std::string val);

std::string base64_decode(std::string val);

}
}

#endif
