#pragma once
#include <string>

class StringConvertible
{
public:
	StringConvertible();
	~StringConvertible();

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);
};

