#include "GameAssert.h"
#include "InputManager.h"

#include "GameApp.h"
#include "PauseOrQuitActor.h"

PauseOrQuitActor::PauseOrQuitActor(GameApp* app)
{
	GAME_CHECK(app != nullptr);
	_app = app;
	_inputMgr = InputManager::GetPtr();
	_isInitialized = true;
}

PauseOrQuitActor::~PauseOrQuitActor()
{
}

void PauseOrQuitActor::Tick(float deltaSeconds)
{
	if (_inputMgr->GetKeyPress(EKey::ESCAPE) == EPress::PRESSED)
	{
		_app->SetDoneLoop(true);
	}
}

void PauseOrQuitActor::Render()
{
}

void PauseOrQuitActor::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_app = nullptr;
	_isInitialized = false;
}