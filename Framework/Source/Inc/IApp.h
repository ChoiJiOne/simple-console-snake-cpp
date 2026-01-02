#pragma once

#include <functional>
#include <memory>

#include "ActorManager.h"
#include "ConsoleManager.h"
#include "GameMacro.h"
#include "GameTimer.h"
#include "InputManager.h"
#include "RenderManager.h"

class IApp
{
public:
	IApp() = default;
	virtual ~IApp();

	virtual void Startup();
	virtual void Shutdown();

	void Run();
	void SetDoneLoop(bool isDoneLoop) { _isDoneLoop = isDoneLoop; }
	void SetProcessTick(const std::function<void(float)>& processTick) { _processTick = processTick; }

protected:
	bool _isInitialized = false;

	ConsoleManager* _consoleMgr = nullptr;
	InputManager* _inputMgr = nullptr;
	RenderManager* _renderMgr = nullptr;
	ActorManager* _actorMgr = nullptr;

private:
	void UpdateTick();

private:
	bool _isDoneLoop = false;

	std::function<void(float)> _processTick;

	GameTimer _timer;
};