#include "ConsoleManager.h"
#include "WindowsAssert.h"

void ConsoleManager::Startup()
{
	if (_isInitialized)
	{
		return; // TODO: 여기에 에러 처리 필요.
	}

	_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WINDOWS_CHECK(_outputHandle != INVALID_HANDLE_VALUE);

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
	WINDOWS_CHECK(SetConsoleCursorPosition(_outputHandle, cursorPos));
}

void ConsoleManager::SetVisibleCursor(bool isVisible)
{
	CONSOLE_CURSOR_INFO info;

	WINDOWS_CHECK(GetConsoleCursorInfo(_outputHandle, &info));
	info.bVisible = isVisible;
	WINDOWS_CHECK(SetConsoleCursorInfo(_outputHandle, &info));
}

void ConsoleManager::SetTitle(const std::string_view& title)
{
	WINDOWS_CHECK(SetConsoleTitle(title.data()));
}

void ConsoleManager::Clear()
{
	COORD topLeftPos = { 0 ,0 };
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	WINDOWS_CHECK(GetConsoleScreenBufferInfo(_outputHandle, &screen));
	WINDOWS_CHECK(FillConsoleOutputCharacterA(_outputHandle, WHITE_SPACE, screen.dwSize.X * screen.dwSize.Y, topLeftPos, &written));
	WINDOWS_CHECK(FillConsoleOutputAttribute(
		_outputHandle, 
		FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, 
		topLeftPos, 
		&written
	));
	WINDOWS_CHECK(SetConsoleCursorPosition(_outputHandle, topLeftPos));
}

void ConsoleManager::ClearRegion(int32_t x, int32_t y, int32_t width, int32_t height)
{
	width = width < 0 ? -width : width;
	height = height < 0 ? -height : height;

	for (int32_t dx = 0; dx < width; ++dx)
	{
		for (int32_t dy = 0; dy < height; ++dy)
		{
			Print(x + dx, y + dy, WHITE_SPACE);
		}
	}
}

void ConsoleManager::Print(int32_t x, int32_t y, char c)
{
	MoveCursor(x, y);
	WINDOWS_CHECK(WriteConsoleA(_outputHandle, &c, CHAR_SIZE, nullptr, nullptr));
}

void ConsoleManager::Print(int32_t x, int32_t y, const std::string_view& str)
{
	MoveCursor(x, y);
	WINDOWS_CHECK(WriteConsoleA(_outputHandle, reinterpret_cast<const void*>(str.data()), static_cast<DWORD>(str.size()), nullptr, nullptr));
}