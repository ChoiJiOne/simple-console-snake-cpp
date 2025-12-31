#include "GameApp.h"
#include "GameAssert.h"

GameApp::~GameApp()
{
	if (_isInitialized)
	{
		Shutdown();
	}
}

void GameApp::Startup()
{
	if (_isInitialized)
	{
		return; // TODO: 에러 로그 처리 필요.
	}

	_consoleMgr = ConsoleManager::GetPtr();
	_inputMgr = InputManager::GetPtr();
	_renderMgr = RenderManager::GetPtr();

	_consoleMgr->Startup();
	_inputMgr->Startup();
	_renderMgr->Startup();

	_consoleMgr->SetVisibleCursor(false);
	_consoleMgr->SetTitle("Snake"); // TODO: 하드 코딩 제거 필요.

	_isInitialized = true;
}

void GameApp::Run()
{
	// TODO: 테스트 코드 (삭제 필요)
	int32_t x = 10;
	int32_t y = 10;
	_context.SetTile(x, y, ETile::HEAD);

	_timer.Start();

	bool isDone = false;
	while (!isDone)
	{
		UpdateTick();

		int32_t newX = x;
		int32_t newY = y;

		if (_inputMgr->GetKeyPress(EKey::LEFT) == EPress::PRESSED)
		{
			newX--;
		}

		if (_inputMgr->GetKeyPress(EKey::RIGHT) == EPress::PRESSED)
		{
			newX++;
		}

		if (_inputMgr->GetKeyPress(EKey::UP) == EPress::PRESSED)
		{
			newY--;
		}

		if (_inputMgr->GetKeyPress(EKey::DOWN) == EPress::PRESSED)
		{
			newY++;
		}

		if (_context.IsValidTile(newX, newY) && !_context.IsOutline(newX, newY))
		{
			const ETile& tile = _context.GetTile(x, y);

			_context.SetTile(x, y, ETile::EMPTY);

			x = newX;
			y = newY;
			_context.SetTile(x, y, ETile::HEAD);
		}

		RenderManager::Get().Render(&_context);
	}
}

void GameApp::Shutdown()
{
	if (!_isInitialized)
	{
		return; // TODO: 에러 로그 처리 필요.
	}

	_consoleMgr->SetVisibleCursor(true);

	_renderMgr->Shutdown();
	_inputMgr->Shutdown();
	_consoleMgr->Shutdown();

	_renderMgr = nullptr;
	_inputMgr = nullptr;
	_consoleMgr = nullptr;
	_isInitialized = false;
}

void GameApp::UpdateTick()
{
	_timer.Tick();
	_inputMgr->Tick();
}