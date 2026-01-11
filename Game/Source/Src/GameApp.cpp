#include "GameApp.h"
#include "GenericAssert.h"

#include "ContextView.h"
#include "FoodView.h"
#include "GameController.h"
#include "ReadyView.h"
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

	ContextView* contextView = _actorMgr->Create<ContextView>(&_context);
	ReadyView* readyView = _actorMgr->Create<ReadyView>();
	Snake* snake = _actorMgr->Create<Snake>(&_context, 3, EMoveDirection::RIGHT);
	FoodView* foodView = _actorMgr->Create<FoodView>(&_context);
	GameController* gameController = _actorMgr->Create<GameController>(this, &_context);

	std::vector<IActor*> readyStateUpdateActors = 
	{ 
		gameController, 
		contextView,
	};
	std::vector<IActor*> readyStateRenderActors = 
	{ 
		contextView, 
		readyView,
		gameController,
	};
	SetGameStateActors(EGameState::READY, readyStateUpdateActors, readyStateRenderActors, 
		[this, readyView]()
		{
			_context.Reset();
			readyView->Reset();
		});

	std::vector<IActor*> playStateUpdateActors =
	{
		gameController,
		snake,
		foodView,
		contextView,
	};

	std::vector<IActor*> playStateRenderActors =
	{
		contextView,
		snake,
		foodView,
		gameController,
	};
	SetGameStateActors(EGameState::PLAY, playStateUpdateActors, playStateRenderActors,
		[this, snake]()
		{
			snake->Reset();
			_context.TrySpawnFood();
		}
	);
	
	SetProcessTick([this](float deltaSeconds) { ProcessTick(deltaSeconds); });

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

void GameApp::SetGameState(const EGameState& gameState, bool bNeedAction)
{
	_gameState = gameState;

	auto it = _actionMap.find(gameState);
	if (it != _actionMap.end() && it->second != nullptr && bNeedAction)
	{
		const std::function<void()>& action = it->second;
		action();
	}
}

void GameApp::SetGameStateActors(
	const EGameState& gameState, 
	const std::vector<IActor*>& updateActors, 
	const std::vector<IActor*>& renderActors,
	const std::function<void()>& action
)
{
	_actionMap[gameState] = action;
	_updateActorsMap[gameState] = updateActors;
	_renderActorsMap[gameState] = renderActors;
}

void GameApp::ProcessTick(float deltaSeconds)
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
}
