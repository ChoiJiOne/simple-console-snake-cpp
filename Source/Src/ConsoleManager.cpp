#include <iostream>
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

void ConsoleManager::SetVisibleCursor(bool isVisible)
{
	CONSOLE_CURSOR_INFO info;

	assert(GetConsoleCursorInfo(_outputHandle, &info));
	info.bVisible = isVisible;
	assert(SetConsoleCursorInfo(_outputHandle, &info));
}

void ConsoleManager::SetTitle(const std::string_view& title)
{
	assert(SetConsoleTitle(title.data()));
}

void ConsoleManager::Print(int32_t x, int32_t y, char c)
{
	MoveCursor(x, y);
	assert(WriteConsoleA(_outputHandle, &c, 1, nullptr, nullptr));
}

void ConsoleManager::Print(int32_t x, int32_t y, const std::string_view& str)
{
	MoveCursor(x, y);
	assert(WriteConsoleA(_outputHandle, reinterpret_cast<const void*>(str.data()), static_cast<DWORD>(str.size()), nullptr, nullptr));
}