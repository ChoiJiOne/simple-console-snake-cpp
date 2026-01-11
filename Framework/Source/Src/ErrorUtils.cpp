#include <windows.h>

#include "ErrorUtils.h"
#include "StringUtils.h"

void ErrorUtils::ReportGenericAssertion(const char* expression, const char* file, uint32_t line, const std::string& description)
{
	std::string errMsg = StringUtils::PrintF(
		"Assertion check point failed!\nFile: %s\nLine: %d\nExpression: %s", 
		file, line, expression
	);
	if (!description.empty())
	{
		errMsg += StringUtils::PrintF("\nDescription: %s\n", description.c_str());
	}

	::MessageBoxA(nullptr, errMsg.c_str(), "REPORT GENERIC ASSERTION", MB_ICONERROR | MB_OK);
}

void ErrorUtils::ReportWindowsAssertion(const char* expression, const char* file, uint32_t line, uint32_t errorCode, const std::string& description)
{
	std::string windowsErrMsg = GetWindowsErrorMessage(errorCode);
	std::string errMsg = StringUtils::PrintF(
		"Assertion check point failed!\nFile: %s\nLine: %d\nExpression: %s\nMessage: %s",
		file, line, expression, windowsErrMsg.c_str()
	);
	if (!description.empty())
	{
		errMsg += StringUtils::PrintF("Description: %s\n", description.c_str());
	}

	::MessageBoxA(nullptr, errMsg.c_str(), "REPORT WINDOWS ASSERTION", MB_ICONERROR | MB_OK);
}

std::string ErrorUtils::GetWindowsErrorMessage(uint32_t errorCode)
{
	static char errorMsgBuffer[ERROR_MSG_STRING_BUFFER_SIZE];
	SecureZeroMemory(errorMsgBuffer, sizeof(errorMsgBuffer));
	
	DWORD dwFlags = FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
	DWORD dwLanguageId = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);

	DWORD size = FormatMessageA(dwFlags, nullptr, errorCode, dwLanguageId, &errorMsgBuffer[0], ERROR_MSG_STRING_BUFFER_SIZE, nullptr);
	if (size == 0)
	{
		return StringUtils::PrintF("Unknown Windows error (code=%u)", errorCode);
	}

	return std::string(errorMsgBuffer, size);
}