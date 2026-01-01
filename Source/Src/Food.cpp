#include "GameAssert.h"
#include "Food.h"
#include "MathUtils.h"

Food::Food(GameContext* context)
{
	GAME_CHECK(context != nullptr);
	_context = context;

	_minPosition = { 1, 1 };
	_maxPosition = { _context->GetColSize() - 2, _context->GetRowSize() - 2 };

	Spawn();

	_isInitialized = true;
}

Food::~Food() {}

void Food::Tick(float deltaSeconds)
{
	const ETile& tile = _context->GetTile(_position);
	if (tile != ETile::FOOD)
	{
		Spawn();
		return;
	}
}

void Food::Render()
{
}

void Food::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_context = nullptr;
	_isInitialized = false;
}

void Food::Spawn()
{
	if (!_context->HasEmptyTile())
	{
		return;
	}

	_position = GetValidRandomPosition();
	_context->SetTile(_position, ETile::FOOD);
}

Position Food::GetValidRandomPosition() const
{
	Position randomPosition{ -1, -1 };
	if (!_context->HasEmptyTile())
	{
		return randomPosition;
	}

	// NOTE: 진짜 수상하게 무한루프(?) 돌아야 하는지 확인 필요 (물론 진짜 무한 루프 돌일은 거의 없을거 같지만 혹시 몰라서...)
	bool bFoundRandomPosition = false;
	while (!bFoundRandomPosition)
	{
		randomPosition.x = MathUtils::GenerateRandomInt(_minPosition.x, _maxPosition.x);
		randomPosition.y = MathUtils::GenerateRandomInt(_minPosition.y, _maxPosition.y);

		if (!_context->IsValidTile(randomPosition))
		{
			continue;
		}

		const ETile& tile = _context->GetTile(randomPosition);
		if (tile == ETile::EMPTY)
		{
			bFoundRandomPosition = true;
		}
	}

	return randomPosition;
}
