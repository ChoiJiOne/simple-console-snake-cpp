#include <cassert>
#include <windows.h>

#include "ConsoleManager.h"

void ConsoleManager::Startup()
{
	if (_isInitialized)
	{
		return; // TODO: 여기에 에러 처리 필요.
	}

	_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	_isInitialized = true;
}

void ConsoleManager::Shutdown()
{
	if (!_isInitialized)
	{
		return; // TODO: 여기에 에러 처리 필요
	}

	_outputHandle = nullptr;
	_isInitialized = false;
}

void ConsoleManager::MoveCursor(int32_t x, int32_t y)
{
	COORD cursorPos = { x, y };
	assert(SetConsoleCursorPosition(_outputHandle, cursorPos));
}