#ifndef _MBPARSER_UTILS_H
#define _MBPARSER_UTILS_H

#include <sstream>

template<class T>
bool ProcessItem(const std::string& Source, T& RetVal)
{
	bool Ret=true;
	std::stringstream os;
	os << Source;
	os >> RetVal;
	if (os.fail())
	{
		Ret=false;
		std::cerr << "Error parsing value '" << Source << "'" << std::endl;
	}

	return Ret;
}

#endif
