#pragma once

#include <deque>
#include <map>

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
	void AddBody(const Position& position);

private:
	GameContext* _context = nullptr;
	InputManager* _inputMgr = nullptr;

	EMoveDirection _moveDirection = EMoveDirection::RIGHT;
	std::map<EKey, EMoveDirection> _keyDirectionMap;

	Position _head = { 0, 0 };
	std::deque<Position> _bodys;
};