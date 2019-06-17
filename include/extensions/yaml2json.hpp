#ifndef _NAVAGRAHA_EXTENSIONS_YAML2JSON_H
#define _NAVAGRAHA_EXTENSIONS_YAML2JSON_H

#include <string>

namespace navagraha {
namespace extensions {
	
std::string str_trim_f(std::string a);

bool is_number(std::string str);

std::string check_null(std::string str,std::string tar);

std::string get_json(std::string yamlstr);

}
}

#endif
