#pragma once

#include "ErrorUtils.h"
#include "StringUtils.h"

#if defined(DEBUG_MODE) || defined(REL_WITH_DEB_INFO_MODE) || defined(RELEASE_MODE)
#ifndef WINDOWS_CHECK
#define WINDOWS_CHECK(EXP)\
{\
	if(!(bool)(EXP))\
	{\
		DWORD __errorCode = GetLastError(); \
		ErrorUtils::ReportWindowsAssertion(#EXP, __FILE__, __LINE__, __errorCode);\
		__debugbreak();\
	}\
}
#endif
#ifndef WINDOWS_ASSERT
#define WINDOWS_ASSERT(EXP, ...)\
{\
	if(!(bool)(EXP))\
	{\
		DWORD __errorCode = GetLastError();\
		ErrorUtils::ReportWindowsAssertion(#EXP, __FILE__, __LINE__, __errorCode, StringUtils::PrintF(__VA_ARGS__));\
		__debugbreak();\
	}\
}
#endif
#else // MINSIZEREL
#ifndef WINDOWS_CHECK
#define WINDOWS_CHECK(EXP) ((void)(EXP))
#endif
#ifndef WINDOWS_ASSERT
#define WINDOWS_ASSERT(EXP, ...) ((void)(EXP))
#endif
#endif