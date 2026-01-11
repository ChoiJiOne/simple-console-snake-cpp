#pragma once

#include <map>

#include "IActor.h"

class GameApp;
class GameContext;
class InputManager;

class GameController : public IActor
{
public:
	GameController(GameApp* app, GameContext* context);
	virtual ~GameController();

	DISALLOW_COPY_AND_ASSIGN(GameController);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void ProcessReadyStateTick();
	void ProcessPlayStateTick();

private:
	GameApp* _app = nullptr;
	GameContext* _context = nullptr;
	InputManager* _inputMgr = nullptr;

	std::map<EGameState, std::function<void()>> _stateProcessActionMap;
};