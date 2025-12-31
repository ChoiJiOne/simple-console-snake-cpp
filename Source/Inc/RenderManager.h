#pragma once

#include "IManager.h"

class GameContext;
class ConsoleManager;

class RenderManager : public IManager<RenderManager>
{
public:
	DISALLOW_COPY_AND_ASSIGN(RenderManager);

	void Startup();
	virtual void Shutdown() override;

private:
	friend class IManager<RenderManager>;

	RenderManager() = default;
	virtual ~RenderManager() = default;

private:
	ConsoleManager* _consoleMgr = nullptr;
};