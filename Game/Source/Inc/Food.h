#pragma once

#include "IActor.h"
#include "GameContext.h"

class ConsoleManager;

class Food : public IActor
{
public:
	Food(GameContext* context);
	virtual ~Food();

	DISALLOW_COPY_AND_ASSIGN(Food);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	GameContext* _context = nullptr;
	ConsoleManager* _consoleMgr = nullptr;

	Position _position = { 0, 0 };

	Position _countViewPosition = { 0, 0 };
	bool _isDirty = false;
	int32_t _count = 0;
};