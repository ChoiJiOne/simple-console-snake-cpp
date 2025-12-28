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
	COORD cursorPos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
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

void ConsoleManager::Clear()
{
	COORD topLeftPos = { 0 ,0 };
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	assert(GetConsoleScreenBufferInfo(_outputHandle, &screen));
	assert(FillConsoleOutputCharacterA(_outputHandle, WHITE_SPACE, screen.dwSize.X * screen.dwSize.Y, topLeftPos, &written));
	assert(FillConsoleOutputAttribute(
		_outputHandle, 
		FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, 
		topLeftPos, 
		&written
	));
	assert(SetConsoleCursorPosition(_outputHandle, topLeftPos));
}

void ConsoleManager::Print(int32_t x, int32_t y, char c)
{
	MoveCursor(x, y);
	assert(WriteConsoleA(_outputHandle, &c, CHAR_SIZE, nullptr, nullptr));
}

void ConsoleManager::Print(int32_t x, int32_t y, const std::string_view& str)
{
	MoveCursor(x, y);
	assert(WriteConsoleA(_outputHandle, reinterpret_cast<const void*>(str.data()), static_cast<DWORD>(str.size()), nullptr, nullptr));
}