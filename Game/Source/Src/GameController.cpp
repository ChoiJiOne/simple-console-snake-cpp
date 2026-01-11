#include "GenericAssert.h"
#include "InputManager.h"

#include "GameApp.h"
#include "GameContext.h"
#include "GameController.h"

GameController::GameController(GameApp* app, GameContext* context)
{
	CHECK(app != nullptr);
	_app = app;

	CHECK(context != nullptr);
	_context = context;

	_inputMgr = InputManager::GetPtr();

	_stateProcessActionMap[EGameState::READY] = [this]() { ProcessReadyStateTick(); };
	_stateProcessActionMap[EGameState::PLAY] = [this]() { ProcessPlayStateTick(); };
	_stateProcessActionMap[EGameState::PAUSE] = [this]() { ProcessPauseStateTick(); };
	_stateProcessActionMap[EGameState::GAME_OVER] = [this]() { ProcessGameOverStateTick(); };

	_isInitialized = true;
}

GameController::~GameController()
{
}

void GameController::Tick(float deltaSeconds)
{
	auto it = _stateProcessActionMap.find(_app->GetGameState());
	if (it != _stateProcessActionMap.end() && it->second != nullptr)
	{
		const std::function<void()>& processStateTick = it->second;
		processStateTick();
	}
}

void GameController::Render()
{
}

void GameController::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_app = nullptr;
	_context = nullptr;
	_isInitialized = false;
}

void GameController::ProcessReadyStateTick()
{
	if (_inputMgr->GetKeyPress(EKey::ESCAPE) == EPress::PRESSED)
	{
		_app->SetDoneLoop(true);
	}
	else if (_inputMgr->GetKeyPress(EKey::SPACE) == EPress::PRESSED)
	{
		_app->SetGameState(EGameState::PLAY);
	}
}

void GameController::ProcessPlayStateTick()
{
	if (_context->IsGameOver())
	{
		_app->SetGameState(EGameState::GAME_OVER);
		return;
	}

	if (_inputMgr->GetKeyPress(EKey::ESCAPE) == EPress::PRESSED)
	{
		_app->SetGameState(EGameState::PAUSE);
	}
}

void GameController::ProcessPauseStateTick()
{
	if (_inputMgr->GetKeyPress(EKey::ESCAPE) == EPress::PRESSED)
	{
		_app->SetGameState(EGameState::PLAY, false);
	}
}

void GameController::ProcessGameOverStateTick()
{
	if (_inputMgr->GetKeyPress(EKey::SPACE) == EPress::PRESSED)
	{
		_app->SetGameState(EGameState::PLAY);
		return;
	}

	if (_inputMgr->GetKeyPress(EKey::ESCAPE) == EPress::PRESSED)
	{
		_app->SetDoneLoop(true);
	}
}
