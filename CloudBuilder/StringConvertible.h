#pragma once
#include <string>

class StringConvertible
{
public:
	StringConvertible();
	~StringConvertible();

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);
};

