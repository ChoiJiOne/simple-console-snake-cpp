#include <windows.h>

#include "StringUtils.h"

char StringUtils::_charBuffer[MAX_STRING_BUFFER_SIZE];
wchar_t StringUtils::_wcharBuffer[MAX_STRING_BUFFER_SIZE];

std::string StringUtils::PrintF(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int32_t size = vsnprintf_s(_charBuffer, MAX_STRING_BUFFER_SIZE, format, args);
	va_end(args);

	return std::string(_charBuffer, size);
}

std::wstring StringUtils::PrintF(const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	int32_t size = _vsnwprintf_s(_wcharBuffer, MAX_STRING_BUFFER_SIZE, format, args);
	va_end(args);

	return std::wstring(_wcharBuffer, size);
}