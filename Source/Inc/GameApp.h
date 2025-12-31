#pragma once

#include <memory>

#include "ActorManager.h"
#include "ConsoleManager.h"
#include "GameContext.h"
#include "GameMacro.h"
#include "GameTimer.h"
#include "InputManager.h"
#include "RenderManager.h"

class GameApp
{
public:
	GameApp() = default;
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	void Startup();
	void Run();
	void Shutdown();

private:
	void UpdateTick();

private:
	bool _isInitialized = false;

	ConsoleManager* _consoleMgr = nullptr;
	InputManager* _inputMgr = nullptr;
	RenderManager* _renderMgr = nullptr;
	ActorManager* _actorMgr = nullptr;

	GameTimer _timer;

	std::vector<IActor*> _updateActors;
	std::vector<IActor*> _renderActors;

private: // 게임 특화 로직
	GameContext _context;
};