#include "ConsoleManager.h"
#include "GenericAssert.h"

#include "GameStateView.h"
#include "StringUtils.h"

GameStateView::GameStateView(GameApp* app)
{
	CHECK(app != nullptr);
	_app = app;
	_consoleMgr = ConsoleManager::GetPtr();

	_stateTextMap =
	{
		{ EGameState::READY, "READY" },
		{ EGameState::PLAY, "PLAY" },
		{ EGameState::PAUSE, "PAUSE" },
		{ EGameState::GAME_OVER, "GAME OVER" },
	};

	_stateTextRegionWidth = 20;
	_stateTextRegionHeight = 1;
	_stateTextViewPositon = { 22, 11 };

	_isInitialized = true;
}

GameStateView::~GameStateView()
{
}

void GameStateView::Tick(float deltaSeconds)
{
	const EGameState& currentState = _app->GetGameState();
	if (_state != currentState)
	{
		_state = currentState;
		_isDirty = true;
	}
}

void GameStateView::Render()
{
	if (!_isDirty)
	{
		return;
	}

	auto it = _stateTextMap.find(_state);
	CHECK(it != _stateTextMap.end());

	_consoleMgr->ClearRegion(_stateTextViewPositon.x, _stateTextViewPositon.y, _stateTextRegionWidth, _stateTextRegionHeight); // TODO: 이거 없으면 텍스트 곂쳐보이는 이슈 있는데, 더 좋은 방법 있으면 수정 필요.
	_consoleMgr->Print(_stateTextViewPositon.x, _stateTextViewPositon.y, StringUtils::PrintF("STATE: %s", it->second.c_str()));

	_isDirty = false;
}

void GameStateView::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_app = nullptr;
	_consoleMgr = nullptr;
	_isInitialized = false;
}

