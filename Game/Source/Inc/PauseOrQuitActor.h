#pragma once

#include "IActor.h"

class GameApp;
class InputManager;

class PauseOrQuitActor : public IActor
{
public:
	PauseOrQuitActor(GameApp* app);
	virtual ~PauseOrQuitActor();

	DISALLOW_COPY_AND_ASSIGN(PauseOrQuitActor);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	GameApp* _app = nullptr;
	InputManager* _inputMgr = nullptr;
};