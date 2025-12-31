#pragma once

#include <windows.h>

#include "ErrorUtils.h"
#include "StringUtils.h"

#if defined(DEBUG_MODE) || defined(REL_WITH_DEB_INFO_MODE) || defined(RELEASE_MODE)
#ifndef GAME_CHECK
#define GAME_CHECK(EXP)\
{\
	if(!(bool)(EXP))\
	{\
		ErrorUtils::ReportAssertion(#EXP, __FILE__, __LINE__);\
		__debugbreak();\
	}\
}
#endif
#ifndef GAME_ASSERT
#define GAME_ASSERT(EXP, ...)\
{\
	if(!(bool)(EXP))\
	{\
		ErrorUtils::ReportAssertion(#EXP, __FILE__, __LINE__, StringUtils::PrintF(__VA_ARGS__));\
		__debugbreak();\
	}\
}
#endif
#else // MINSIZEREL
#ifndef GAME_CHECK
#define GAME_CHECK(EXP) ((void)(EXP))
#endif
#ifndef GAME_ASSERT
#define GAME_ASSERT(EXP, ...) ((void)(EXP))
#endif
#endif