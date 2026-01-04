#pragma once

#include "IActor.h"
#include "GameContext.h"

class ConsoleManager;

class LevelView : public IActor
{
public:
	LevelView(GameContext* context);
	virtual ~LevelView();

	DISALLOW_COPY_AND_ASSIGN(LevelView);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	GameContext* _context = nullptr;
	ConsoleManager* _consoleMgr = nullptr;

	Position _levelViewPosition = { 0, 0 };
	Position _levelStepViewPosition = { 0, 0 };
	bool _isDirty = false;
	int32_t _level = 0;
};