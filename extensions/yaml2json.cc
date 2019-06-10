#include "extensions/yaml2json.hpp"
#include <sstream>

#include <iostream>

namespace navagraha{
	namespace extensions{
class yaml2json
{
	private:
		static std::string strTrimF(std::string a)
		{
			int i = 0;
			while (a[i]==' ') i++;
			a = a.substr(i);
			return a;
		}
		static bool IsNumber(std::string str)
		{
			std::stringstream sin(str);  
			double d;  
			char c;  
			if(!(sin >> d))  
				return false;  
			if (sin >> c)  
				return false;  
			return true;  
		}
		static std::string checkNull(std::string str,std::string tar)
		{
			int len = tar.length();
			if (str.find(tar)!=-1) str = str.replace(str.find(tar), len, ": null" + tar.substr(len-1));
			return str;
		}
	public:
		static std::string getJson(std::string yamlstr)
		{
			std::string jsonstr, linestr, keystr, valuestr;char markstr[] = "";
			int i,nowkey,lastkey,top;
			top = -1;lastkey = -1;
			while (yamlstr != "")
			{
				linestr = yamlstr.substr(0,yamlstr.find('\n')); 
				if (yamlstr.find('\n') != -1)
				{
					yamlstr = yamlstr.substr(yamlstr.find('\n') + 1);
				}
				else
				{
					yamlstr = "";
				}
				if (linestr == "---") continue;
				keystr = linestr.substr(0,linestr.find(':'));
				i = 0; 
				while (keystr[i] == ' ') i++;
				nowkey = i;
				if (i == lastkey)
				{
					jsonstr.append(",");
					if (keystr[i] == '-')
					{
						i = i + 2;
						if (linestr.find(':')!=-1) jsonstr.append("{");
					}
				}
				else
				{
					if (i > lastkey)
					{
						if (keystr[i] == '-') 
						{
							i = i + 2;
							top++;
							markstr[top] = ']';
							jsonstr.append("["); 
						}
						if (linestr.find(':')!=-1)
						{
							if (keystr[i-2] != '-') 
							{
								top++;
								markstr[top] = '}';
							}
							jsonstr.append("{");
						}
					}
					else
					{
						jsonstr.append(1, markstr[top] );
						jsonstr.append(1, ',');
						top--;
					}
				}
				jsonstr.append("\"" + keystr.substr(i) + "\"");
				lastkey = nowkey;
				if (linestr.find(':') != -1)
				{
					jsonstr.append(":");
					valuestr = linestr.substr(linestr.find(':') + 1);
				} 
				else
				{
					valuestr = "";
				} 
				valuestr = strTrimF(valuestr);
				if (valuestr!="")
				{
					if (!IsNumber(valuestr))
						jsonstr.append(" \"" + valuestr + "\"");
					else
						jsonstr.append(" " + valuestr);
				}
				if ((linestr.find('-')!=-1)&&(linestr.find(':')!=-1)) jsonstr.append(1,'}');
			}
			while (top > -1)
			{
				jsonstr.append(1,markstr[top]);
				top--;
			}
			jsonstr = checkNull(jsonstr, ":}");
			jsonstr = checkNull(jsonstr, ":,");
			return jsonstr;
		}
};
}
}