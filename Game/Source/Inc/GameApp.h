#pragma once

#include "IApp.h"
#include "GameContext.h"

class GameApp : public IApp
{
public:
	GameApp() = default;
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;

private:
	void ProcessTick(float deltaSeconds);

private:
	std::vector<IActor*> _updateActors;
	std::vector<IActor*> _renderActors;
	GameContext _context;
};