#pragma once

#include "ErrorUtils.h"
#include "StringUtils.h"

#if defined(DEBUG_MODE) || defined(REL_WITH_DEB_INFO_MODE) || defined(RELEASE_MODE)
#ifndef CHECK
#define CHECK(EXP)\
{\
	if(!(bool)(EXP))\
	{\
		ErrorUtils::ReportGenericAssertion(#EXP, __FILE__, __LINE__);\
		__debugbreak();\
	}\
}
#endif
#ifndef ASSERT
#define ASSERT(EXP, ...)\
{\
	if(!(bool)(EXP))\
	{\
		ErrorUtils::ReportGenericAssertion(#EXP, __FILE__, __LINE__, StringUtils::PrintF(__VA_ARGS__));\
		__debugbreak();\
	}\
}
#endif
#else // MINSIZEREL
#ifndef CHECK
#define CHECK(EXP) ((void)(EXP))
#endif
#ifndef ASSERT
#define ASSERT(EXP, ...) ((void)(EXP))
#endif
#endif