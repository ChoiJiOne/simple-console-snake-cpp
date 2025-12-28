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
	while (!isDone)
	{
		int32_t newX = x;
		int32_t newY = y;

		InputManager::Get().Tick();

		if (InputManager::Get().GetKeyPress(EKey::LEFT) == EPress::PRESSED)
		{	
			newX--;
		}

		if (InputManager::Get().GetKeyPress(EKey::RIGHT) == EPress::PRESSED)
		{
			newX++;
		}

		if (InputManager::Get().GetKeyPress(EKey::UP) == EPress::PRESSED)
		{
			newY--;
		}

		if (InputManager::Get().GetKeyPress(EKey::DOWN) == EPress::PRESSED)
		{
			newY++;
		}

		if (context.IsValidTile(newX, newY) && !context.IsOutline(newX, newY))
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