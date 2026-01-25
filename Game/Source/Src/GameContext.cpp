#include "GenericAssert.h"
#include "MathUtils.h"

#include "GameContext.h"


GameContext::GameContext()
{
	_tiles = std::vector<ETile>(_rowSize * _colSize, ETile::EMPTY);
	_minPosition = { 1, 1 };
	_maxPosition = { _colSize - 2, _rowSize - 2 };
}

GameContext::~GameContext()
{
}

void GameContext::Reset()
{
	for (int y = 0; y < _rowSize; ++y)
	{
		for (int x = 0; x < _colSize; ++x)
		{
			ETile tile = IsOutline(x, y) ? ETile::WALL : ETile::EMPTY;
			SetTile(x, y, tile);
		}
	}

	_isGameOver = false;

	_isDirtyScore = true;
	_isDirtyBestScore = true;

	_currentScore = _spawnedFoodCount - 1; // NOTE: 이전 기록 있다면 사용.
	_bestScore = MathUtils::Max(_bestScore, _currentScore);

	_currentScore = 0;
	_spawnedFoodCount = 0;

	if (_snakeStateResetFn != nullptr)
	{
		_snakeStateResetFn(); // 뱀 상태 초기화
		TrySpawnFood(); // 음식 스폰.
	}

}

void GameContext::SetTile(int32_t x, int32_t y, const ETile& tile, bool bForceSet)
{
	CHECK(IsValidTile(x, y));

	int32_t offset = y * _colSize + x;
	if (!bForceSet && _tiles[offset] == tile)
	{
		return;
	}

	_tiles[offset] = tile;
	_isDirtyTile = true;
}

void GameContext::SetTile(const Position& position, const ETile& tile)
{
	return SetTile(position.x, position.y, tile);
}

const ETile& GameContext::GetTile(int32_t x, int32_t y) const
{
	CHECK(IsValidTile(x, y));

	int32_t offset = y * _colSize + x;
	return _tiles[offset];
}

const ETile& GameContext::GetTile(const Position& position) const
{
	return GetTile(position.x, position.y);
}

bool GameContext::IsOutline(int32_t x, int32_t y) const
{
	return (x <= 0 || x >= _colSize - 1) || (y <= 0 || y >= _rowSize - 1);
}

bool GameContext::IsOutline(const Position& position) const
{
	return IsOutline(position.x, position.y);
}

bool GameContext::HasEmptyTile() const
{
	for (const auto& tile : _tiles)
	{
		if (tile == ETile::EMPTY)
		{
			return true;
		}
	}

	return false;
}

bool GameContext::TrySpawnFood()
{
	if (!HasEmptyTile())
	{
		return false;
	}

	Position foodPosition = GetRandomEmptyPosition();
	SetTile(foodPosition, ETile::FOOD);
	_spawnedFoodCount++;

	_currentScore = _spawnedFoodCount - 1;
	_isDirtyScore = true;

	return true;
}

bool GameContext::IsValidTile(int32_t x, int32_t y) const
{
	return (0 <= x && x <= _colSize - 1) && (0 <= y && y <= _rowSize - 1);
}

bool GameContext::IsValidTile(const Position& position) const
{
	return IsValidTile(position.x, position.y);
}

bool GameContext::CanMoveTo(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY)
{
	if (!IsValidTile(srcX, srcY) || IsOutline(srcX, srcY) || !IsValidTile(dstX, dstY) || IsOutline(dstX, dstY))
	{
		return false;
	}

	ETile srcTile = GetTile(srcX, srcY);
	ETile dstTile = GetTile(dstX, dstY);

	bool bCanMove = false;
	if (srcTile == ETile::HEAD)
	{
		bCanMove = (dstTile == ETile::EMPTY || dstTile == ETile::FOOD); // NOTE: 머리만 예외적으로 먹이가 있는 곳을 움직일 수 있음.
	}
	else
	{
		bCanMove = (dstTile == ETile::EMPTY);
	}

	return bCanMove;
}

bool GameContext::CanMoveTo(const Position& srcPosition, const Position& dstPosition)
{
	return CanMoveTo(srcPosition.x, srcPosition.y, dstPosition.x, dstPosition.y);
}

void GameContext::MoveTo(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY, bool bKeepSrc)
{
	if (!CanMoveTo(srcX, srcY, dstX, dstY))
	{
		return;
	}

	ETile srcTile = GetTile(srcX, srcY);
	ETile dstTile = GetTile(dstX, dstY);

	SetTile(dstX, dstY, srcTile);
	if (!bKeepSrc)
	{
		SetTile(srcX, srcY, ETile::EMPTY);
	}
}

void GameContext::MoveTo(const Position& srcPosition, const Position& dstPosition, bool bKeepSrc)
{
	MoveTo(srcPosition.x, srcPosition.y, dstPosition.x, dstPosition.y, bKeepSrc);
}

bool GameContext::CanSwap(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY)
{
	if (!IsValidTile(srcX, srcY) || IsOutline(srcX, srcY) || !IsValidTile(dstX, dstY) || IsOutline(dstX, dstY))
	{
		return false;
	}

	return true;
}

bool GameContext::CanSwap(const Position& srcPosition, const Position& dstPosition)
{
	return CanSwap(srcPosition.x, srcPosition.y, dstPosition.x, dstPosition.y);
}

void GameContext::Swap(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY)
{
	if (!CanSwap(srcX, srcY, dstX, dstY))
	{
		return;
	}

	ETile srcTile = GetTile(srcX, srcY);
	ETile dstTile = GetTile(dstX, dstY);

	SetTile(dstX, dstY, srcTile, true);
	SetTile(srcX, srcY, dstTile, true);
}

void GameContext::Swap(const Position& srcPosition, const Position& dstPosition)
{
	Swap(srcPosition.x, srcPosition.y, dstPosition.x, dstPosition.y);
}

bool GameContext::CanMove(int32_t x, int32_t y, const EMoveDirection& moveDirection)
{
	int32_t moveX = x;
	int32_t moveY = y;

	moveX += moveDirection == EMoveDirection::LEFT ? -1 : moveDirection == EMoveDirection::RIGHT ? 1 : 0;
	moveY += moveDirection == EMoveDirection::UP ? -1 : moveDirection == EMoveDirection::DOWN ? 1 : 0;

	return CanMoveTo(x, y, moveX, moveY);
}

bool GameContext::CanMove(const Position& position, const EMoveDirection& moveDirection)
{
	return CanMove(position.x, position.y, moveDirection);
}

// TODO: CanMove / Move 반복되는 부분 정리 필요.
EMoveResult GameContext::Move(int32_t& x, int32_t& y, const EMoveDirection& moveDirection, bool bKeepSrc)
{
	if (!CanMove(x, y, moveDirection))
	{
		return EMoveResult::BLOCKED;
	}

	int32_t moveX = x;
	int32_t moveY = y;

	moveX += moveDirection == EMoveDirection::LEFT ? -1 : moveDirection == EMoveDirection::RIGHT ? 1 : 0;
	moveY += moveDirection == EMoveDirection::UP ? -1 : moveDirection == EMoveDirection::DOWN ? 1 : 0;

	EMoveResult result = (GetTile(moveX, moveY) == ETile::FOOD) ? EMoveResult::CONSUME : EMoveResult::MOVED;

	MoveTo(x, y, moveX, moveY, bKeepSrc);
	x = moveX;
	y = moveY;

	return result;
}

EMoveResult GameContext::Move(Position& position, const EMoveDirection& moveDirection, bool bKeepSrc)
{
	return Move(position.x, position.y, moveDirection, bKeepSrc);
}

Position GameContext::GetRandomEmptyPosition() const
{
	Position randomPosition{ -1, -1 };
	if (!HasEmptyTile())
	{
		return randomPosition;
	}

	// NOTE: 진짜 수상하게 무한루프(?) 돌아야 하는지 확인 필요 (물론 진짜 무한 루프 돌일은 거의 없을거 같지만 혹시 몰라서...)
	bool bFoundRandomPosition = false;
	while (!bFoundRandomPosition)
	{
		randomPosition.x = MathUtils::GenerateRandomInt(_minPosition.x, _maxPosition.x);
		randomPosition.y = MathUtils::GenerateRandomInt(_minPosition.y, _maxPosition.y);

		if (!IsValidTile(randomPosition))
		{
			continue;
		}

		const ETile& tile = GetTile(randomPosition);
		if (tile == ETile::EMPTY)
		{
			bFoundRandomPosition = true;
		}
	}

	return randomPosition;
}