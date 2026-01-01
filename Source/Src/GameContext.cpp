#include "ConsoleManager.h"
#include "GameAssert.h"
#include "GameContext.h"

GameContext::GameContext()
{
	_tiles = std::vector<ETile>(_rowSize * _colSize, ETile::EMPTY);
	for (int y = 0; y < _rowSize; ++y)
	{
		for (int x = 0; x < _colSize; ++x)
		{
			if (IsOutline(x, y))
			{
				SetTile(x, y, ETile::WALL);
			}
		}
	}
}

GameContext::~GameContext()
{
}

void GameContext::SetTile(int32_t x, int32_t y, const ETile& tile)
{
	GAME_CHECK(IsValidTile(x, y));

	int32_t offset = y * _colSize + x;
	if (_tiles[offset] == tile)
	{
		return;
	}

	_tiles[offset] = tile;
	_isDirty = true;
}

const ETile& GameContext::GetTile(int32_t x, int32_t y)
{
	GAME_CHECK(IsValidTile(x, y));

	int32_t offset = y * _colSize + x;
	return _tiles[offset];
}

bool GameContext::IsOutline(int32_t x, int32_t y)
{
	return (x <= 0 || x >= _colSize - 1) || (y <= 0 || y >= _rowSize - 1);
}

bool GameContext::IsValidTile(int32_t x, int32_t y)
{
	return (0 <= x && x <= _colSize - 1) && (0 <= y && y <= _rowSize - 1);
}

bool GameContext::CanMoveTo(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY)
{
	if (!IsValidTile(srcX, srcY) || IsOutline(srcX, srcY) || !IsValidTile(dstX, dstY) || IsOutline(dstX, dstY))
	{
		return false;
	}
	
	const ETile& srcTile = GetTile(srcX, srcY);
	const ETile& dstTile = GetTile(dstX, dstY);

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

void GameContext::MoveTo(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY)
{
	if (!CanMoveTo(srcX, srcY, dstX, dstY))
	{
		return;
	}

	const ETile& srcTile = GetTile(srcX, srcY);
	const ETile& dstTile = GetTile(dstX, dstY);

	SetTile(dstX, dstY, srcTile);
	SetTile(srcX, srcY, ETile::EMPTY);
}

bool GameContext::CanSwap(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY)
{
	if (!IsValidTile(srcX, srcY) || IsOutline(srcX, srcY) || !IsValidTile(dstX, dstY) || IsOutline(dstX, dstY))
	{
		return false;
	}

	return true;
}

void GameContext::Swap(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY)
{
	if (!CanSwap(srcX, srcY, dstX, dstY))
	{
		return;
	}

	const ETile& srcTile = GetTile(srcX, srcY);
	const ETile& dstTile = GetTile(dstX, dstY);

	SetTile(dstX, dstY, srcTile);
	SetTile(srcX, srcY, dstTile);
}