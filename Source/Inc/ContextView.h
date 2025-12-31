#pragma once

#include <map>

#include "IActor.h"
#include "GameContext.h"

class ConsoleManager;

class ContextView : public IActor
{
public:
	ContextView(GameContext* context);
	virtual ~ContextView();

	DISALLOW_COPY_AND_ASSIGN(ContextView);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	ConsoleManager* _consoleMgr = nullptr;
	GameContext* _context = nullptr;
	std::map<ETile, char> _tileCharMap;
};