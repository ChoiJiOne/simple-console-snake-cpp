#include "GameApp.h"
#include "GameAssert.h"

#include "ContextView.h"
#include "Food.h"
#include "Snake.h"

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
	_actorMgr = ActorManager::GetPtr();

	_consoleMgr->Startup();
	_inputMgr->Startup();
	_renderMgr->Startup();
	_actorMgr->Startup();

	_consoleMgr->SetVisibleCursor(false);
	_consoleMgr->SetTitle("Snake"); // TODO: 하드 코딩 제거 필요.
	_consoleMgr->Clear();

	IActor* contextView = _actorMgr->Create<ContextView>(&_context);
	IActor* snake = _actorMgr->Create<Snake>(&_context, 3, EMoveDirection::RIGHT, 0.5f);
	IActor* food = _actorMgr->Create<Food>(&_context);

	_updateActors = 
	{
		snake,
		food,
		contextView,
	};

	_renderActors =
	{
		contextView,
		snake,
		food,
	};

	_isInitialized = true;
}

void GameApp::Run()
{
	_timer.Start();

	bool isDone = false;
	while (!isDone)
	{
		UpdateTick();

		// TODO: 일단 ESC 누르면 루프 종료.
		if (_inputMgr->GetKeyPress(EKey::ESCAPE) == EPress::PRESSED)
		{
			isDone = true;
		}
		
		for (auto& actor : _updateActors)
		{
			actor->Tick(_timer.GetDeltaSeconds());
		}

		for (auto& actor : _renderActors)
		{
			actor->Render();
		}
	}
}

void GameApp::Shutdown()
{
	if (!_isInitialized)
	{
		return; // TODO: 에러 로그 처리 필요.
	}

	_consoleMgr->SetVisibleCursor(true);

	_actorMgr->Shutdown();
	_renderMgr->Shutdown();
	_inputMgr->Shutdown();
	_consoleMgr->Shutdown();

	_actorMgr = nullptr;
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