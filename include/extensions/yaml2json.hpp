#ifndef _NAVAGRAHA_EXTENSIONS_YAML2JSON_H
#define _NAVAGRAHA_EXTENSIONS_YAML2JSON_H

#include <string>

namespace navagraha {
namespace extensions {
class yaml2json{
private:
	static std::string strTrimF(std::string a);
	static bool IsNumber(std::string str);
	static std::string checkNumm(std::string str,std::string tar);
public:
	static std::string getJson(std::string yamlstr);
}
}
}

#endif
