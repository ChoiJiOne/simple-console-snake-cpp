#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "GameMacro.h"

enum class ETile
{
	EMPTY = 0x00,
	WALL = 0x01,
	BODY = 0x02,
	HEAD = 0x03,
	FOOD = 0x04,
};

class GameContext
{
public:
	GameContext();
	virtual ~GameContext();

	DISALLOW_COPY_AND_ASSIGN(GameContext);

	void SetTile(int32_t x, int32_t y, const ETile& tile);
	void SetDirty(bool isDirty) { _isDirty = isDirty; }

	const ETile& GetTile(int32_t x, int32_t y);
	const int32_t& GetRowSize() const { return _rowSize; }
	const int32_t& GetColSize() const { return _colSize; }
	bool IsDirty() const { return _isDirty; }
	bool IsValidTile(int32_t x, int32_t y);
	bool IsOutline(int32_t x, int32_t y);

	bool CanMoveTo(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY);
	void MoveTo(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY);
	bool CanSwap(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY);
	void Swap(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY);

private:
	bool _isDirty = false;

	int32_t _rowSize = 20; // 세로 크기
	int32_t _colSize = 20; // 가로 크기

	std::vector<ETile> _tiles;
};
