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
	IActor* snake = _actorMgr->Create<Snake>(&_context, 3, EMoveDirection::RIGHT);
	IActor* foodView = _actorMgr->Create<FoodView>(&_context);
	IActor* levelView = _actorMgr->Create<LevelView>(&_context);
	IActor* pauseOrQuitActor = _actorMgr->Create<PauseOrQuitActor>(this);

	std::vector<IActor*> updateActors =
	{
		pauseOrQuitActor,
		snake,
		foodView,
		levelView,
		contextView,
	};

	std::vector<IActor*> renderActors =
	{
		contextView,
		snake,
		foodView,
		levelView,
		pauseOrQuitActor,
	};

	SetGameStateActors(EGameState::PLAYING, updateActors, renderActors);

	SetProcessTick([this](float deltaSeconds)
		{
			auto& updateActors = _updateActorsMap.find(_gameState);
			if (updateActors != _updateActorsMap.end()) // TOCO: 못 찾았을 때 에러 처리 필요.
			{
				for (auto& actor : updateActors->second)
				{
					actor->Tick(deltaSeconds);
				}
			}

			auto& renderActors = _renderActorsMap.find(_gameState);
			if (renderActors != _renderActorsMap.end()) // TOCO: 못 찾았을 때 에러 처리 필요.
			{
				for (auto& actor : renderActors->second)
				{
					actor->Render();
				}
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

void GameApp::SetGameStateActors(const EGameState& gameState, const std::vector<IActor*>& updateActors, const std::vector<IActor*>& renderActors)
{
	_updateActorsMap[gameState] = updateActors;
	_renderActorsMap[gameState] = renderActors;
}