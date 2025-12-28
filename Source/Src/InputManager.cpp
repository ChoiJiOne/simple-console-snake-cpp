#include "InputManager.h"

void InputManager::Startup()
{
	if (_isInitialized)
	{
		return; // TODO: 여기에 에러 처리 필요.
	}

	_isInitialized = true;
}

void InputManager::Shutdown()
{
	if (!_isInitialized)
	{
		return; // TODO: 여기에 에러 처리 필요
	}

	// CHECKME: 여기에서 리소스 정리.

	_isInitialized = false;
}