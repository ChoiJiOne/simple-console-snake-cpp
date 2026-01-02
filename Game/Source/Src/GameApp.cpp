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

	IApp::Startup();

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

	SetProcessTick([this](float deltaSeconds)
		{
			ProcessTick(deltaSeconds);
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

void GameApp::ProcessTick(float deltaSeconds)
{
	if (_inputMgr->GetKeyPress(EKey::ESCAPE) == EPress::PRESSED)
	{
		SetDoneLoop(true);
	}

	for (auto& actor : _updateActors)
	{
		actor->Tick(deltaSeconds);
	}

	for (auto& actor : _renderActors)
	{
		actor->Render();
	}
}