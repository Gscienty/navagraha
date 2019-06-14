#ifndef _NAVAGRAHA_EXTENSIONS_YAML2JSON_H
#define _NAVAGRAHA_EXTENSIONS_YAML2JSON_H

#include <string>

namespace navagraha {
	namespace extensions {
		std::string strTrimF(std::string a);
		bool IsNumber(std::string str);
		std::string checkNumm(std::string str,std::string tar);
		std::string getJson(std::string yamlstr);
	}
}

#endif
