#pragma once

#include <windows.h>

#include <cstdint>
#include <string>

class ErrorUtils
{
public:
	static void ReportGenericAssertion(const char* expression, const char* file, uint32_t line, const std::string& description = "");
	static void ReportWindowsAssertion(const char* expression, const char* file, uint32_t line, uint32_t errorCode, const std::string& description = "");

private:
	static std::string GetWindowsErrorMessage(uint32_t errorCode);

private:
	static const uint32_t ERROR_MSG_STRING_BUFFER_SIZE = 1024;
};