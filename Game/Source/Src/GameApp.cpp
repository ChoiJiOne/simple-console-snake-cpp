#include "GameApp.h"
#include "GameAssert.h"

#include "ContextView.h"
#include "FoodView.h"
#include "LevelView.h"
#include "PauseOrQuitActor.h"
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

	IApp::Startup();

	_consoleMgr->SetVisibleCursor(false);
	_consoleMgr->SetTitle("Snake"); // TODO: 하드 코딩 제거 필요.
	_consoleMgr->Clear();

	IActor* contextView = _actorMgr->Create<ContextView>(&_context);
	IActor* snake = _actorMgr->Create<Snake>(&_context, 3, EMoveDirection::RIGHT, 0.5f);
	IActor* foodView = _actorMgr->Create<FoodView>(&_context);
	IActor* levelView = _actorMgr->Create<LevelView>(&_context);
	IActor* pauseOrQuitActor = _actorMgr->Create<PauseOrQuitActor>(this);

	_updateActors = 
	{ 
		pauseOrQuitActor,
		snake,
		foodView,
		levelView,
		contextView,
	};

	_renderActors =
	{
		contextView,
		snake,
		foodView,
		levelView,
		pauseOrQuitActor,
	};

	SetProcessTick([this](float deltaSeconds)
		{
			for (auto& actor : _updateActors)
			{
				actor->Tick(deltaSeconds);
			}

			for (auto& actor : _renderActors)
			{
				actor->Render();
			}
		});

	_isInitialized = true;
}

void GameApp::Shutdown()
{
	if (!_isInitialized)
	{
		return; // TODO: 에러 로그 처리 필요.
	}

	_consoleMgr->SetVisibleCursor(true);

	IApp::Shutdown();
}