#pragma once

#include <list>

#include "IActor.h"
#include "GameContext.h"

class Snake : public IActor
{
public:
	Snake(GameContext* context, int32_t defaultBodyCount, EMoveDirection defaultMoveDirection);
	virtual ~Snake();

	DISALLOW_COPY_AND_ASSIGN(Snake);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	GameContext* _context;

	EMoveDirection _moveDirection = EMoveDirection::RIGHT;

	Position _head = { 0, 0 };
	std::list<Position> _bodys;
};