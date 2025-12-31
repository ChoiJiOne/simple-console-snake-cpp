#include <cassert>

#include "ConsoleManager.h"
#include "GameContext.h"
#include "RenderManager.h"

void RenderManager::Startup()
{
	if (_isInitialized)
	{
		return; // TODO: 여기에 에러 처리 필요.
	}

	_consoleMgr = ConsoleManager::GetPtr();
}

void RenderManager::Shutdown()
{
	if (!_isInitialized)
	{
		return; // TODO: 여기에 에러 처리 필요
	}

	// CHECKME: 여기에서 리소스 정리.
	_consoleMgr = nullptr;
	_isInitialized = false;
}