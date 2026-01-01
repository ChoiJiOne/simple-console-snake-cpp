#pragma once

#include "IActor.h"
#include "GameContext.h"

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
	void Spawn();
	Position GetValidRandomPosition() const;

private:
	GameContext* _context = nullptr;

	Position _minPosition = { 0, 0 };
	Position _maxPosition = { 0, 0 };

	Position _position = { 0, 0 };
};