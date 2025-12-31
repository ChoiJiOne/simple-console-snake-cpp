#pragma once

#include <cstdint>
#include <string>

class StringUtils
{
public:
	static std::string PrintF(const char* format, ...);
	static std::wstring PrintF(const wchar_t* format, ...);
	
private:
	static const uint32_t MAX_STRING_BUFFER_SIZE = 1024;
	static char _charBuffer[MAX_STRING_BUFFER_SIZE];
	static wchar_t _wcharBuffer[MAX_STRING_BUFFER_SIZE];
};