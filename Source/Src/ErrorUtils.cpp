#include <windows.h>

#include "ErrorUtils.h"
#include "StringUtils.h"

void ErrorUtils::ReportAssertion(const char* expression, const char* file, uint32_t line, const std::string& description)
{
	std::string message = StringUtils::PrintF("Assertion check point failed!\nFile : %s\nLine : %d\nExpression : %s", file, line, expression);
	if (!description.empty())
	{
		message += StringUtils::PrintF("\nDescription: %s\n", description.c_str());
	}

	MessageBoxA(nullptr, message.c_str(), "REPORT ASSERTION", MB_ICONERROR | MB_OK);
}