#include <Windows.h>

#include "ConsoleManager.h"
#include "InputManager.h"

#include "GameContext.h"

int main(void)
{
	ConsoleManager::Get().Startup();
	InputManager::Get().Startup();

	ConsoleManager::Get().SetVisibleCursor(false);
	ConsoleManager::Get().SetTitle("Snake");

	GameContext context;
	
	int32_t x = 10;
	int32_t y = 10;

	// 임시 테스트용 코드.
	context.SetTile(x, y, ETile::HEAD);

	bool isDone = false;
	bool isPressed = false;
	while (!isDone)
	{
		isPressed = false;
		int32_t newX = x;
		int32_t newY = y;

		if (HIBYTE(GetAsyncKeyState(VK_DOWN)))
		{
			isPressed = true;
			newY++;
		}
		if (HIBYTE(GetAsyncKeyState(VK_UP)))
		{
			isPressed = true;
			newY--;
		}
		if (HIBYTE(GetAsyncKeyState(VK_LEFT)))
		{
			isPressed = true;
			newX--;
		}
		if (HIBYTE(GetAsyncKeyState(VK_RIGHT)))
		{
			isPressed = true;
			newX++;
		}

		if (context.IsValidTile(newX, newY) &&  isPressed)
		{
			const ETile& tile = context.GetTile(x, y);
			
			context.SetTile(x, y, ETile::EMPTY);

			x = newX;
			y = newY;
			context.SetTile(x, y, ETile::HEAD);
		}

		context.Render();
	}

	ConsoleManager::Get().SetVisibleCursor(true);

	InputManager::Get().Shutdown();
	ConsoleManager::Get().Shutdown();

	return 0;
}