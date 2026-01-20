#include "GameApp.h"
#include "GenericAssert.h"

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

void GameApp::ProcessTick(float deltaSeconds)
{
}
