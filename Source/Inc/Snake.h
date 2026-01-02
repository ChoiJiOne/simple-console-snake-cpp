#pragma once

#include <deque>
#include <map>

#include "IActor.h"
#include "GameContext.h"

class Snake : public IActor
{
public:
	Snake(GameContext* context, int32_t defaultBodyCount, EMoveDirection defaultMoveDirection, float moveIntervalTime);
	virtual ~Snake();

	DISALLOW_COPY_AND_ASSIGN(Snake);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void SetMoveIntervalTime(float moveIntervalTime) { _moveIntervalTime = moveIntervalTime; }

private:
	void AddBody(const Position& position);
	bool UpdateMoveDirection(); // NOTE: 값이 변경된 것이 있으면 TRUE 반환.
	EMoveResult Move();

private:
	GameContext* _context = nullptr;
	InputManager* _inputMgr = nullptr;

	EMoveDirection _moveDirection = EMoveDirection::RIGHT;
	std::map<EKey, EMoveDirection> _keyDirectionMap;

	Position _head = { 0, 0 };
	std::deque<Position> _bodys;

	float _moveElapsedTime = 0.0f;
	float _moveIntervalTime = 0.0f;
	bool _isDead = false;
};