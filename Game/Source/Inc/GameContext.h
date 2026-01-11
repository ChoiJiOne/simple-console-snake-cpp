#pragma once

#include <functional>
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

enum class EMoveDirection
{
	NONE = 0x00,
	LEFT = 0x01,
	RIGHT = 0x02,
	UP = 0x03,
	DOWN = 0x04,
};

enum class EMoveResult
{
	BLOCKED = 0x00,
	MOVED   = 0x01,
	CONSUME = 0x02,
};

// CHECKME: 나중에 하는 일 많아지면 class로 변경!
struct Position
{
	int32_t x;
	int32_t y;
};

class GameContext
{
public:
	GameContext();
	virtual ~GameContext();

	DISALLOW_COPY_AND_ASSIGN(GameContext);

	void Reset();

	void SetTile(int32_t x, int32_t y, const ETile& tile, bool bForceSet = false);
	void SetTile(const Position& position, const ETile& tile);
	void SetDirty(bool isDirty) { _isDirty = isDirty; }
	void SetGameOver(bool isGameOver) { _isGameOver = isGameOver; }
	
	const ETile& GetTile(int32_t x, int32_t y) const;
	const ETile& GetTile(const Position& position) const;
	const int32_t& GetRowSize() const { return _rowSize; }
	const int32_t& GetColSize() const { return _colSize; }
	bool IsDirty() const { return _isDirty; }
	bool IsGameOver() const { return _isGameOver; }
	bool IsValidTile(int32_t x, int32_t y) const;
	bool IsValidTile(const Position& position) const;
	bool IsOutline(int32_t x, int32_t y) const;
	bool IsOutline(const Position& position) const;
	bool HasEmptyTile() const;
	const int32_t& GetSpawnedFoodCount() const { return _spawnedFoodCount; }

	bool TrySpawnFood();

	bool CanMoveTo(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY);
	bool CanMoveTo(const Position& srcPosition, const Position& dstPosition);
	void MoveTo(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY, bool bKeepSrc = false);
	void MoveTo(const Position& srcPosition, const Position& dstPosition, bool bKeepSrc = false);

	bool CanSwap(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY);
	bool CanSwap(const Position& srcPosition, const Position& dstPosition);
	void Swap(int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY);
	void Swap(const Position& srcPosition, const Position& dstPosition);

	bool CanMove(int32_t x, int32_t y, const EMoveDirection& moveDirection);
	bool CanMove(const Position& position, const EMoveDirection& moveDirection);
	EMoveResult Move(int32_t& x, int32_t& y, const EMoveDirection& moveDirection, bool bKeepSrc = false);
	EMoveResult Move(Position& position, const EMoveDirection& moveDirection, bool bKeepSrc = false);

	float GetMoveSpeed() { return _moveSpeed; }

private:
	Position GetRandomEmptyPosition() const;

private:
	bool _isDirty = false;
	bool _isGameOver = false;

	int32_t _rowSize = 20; // 세로 크기
	int32_t _colSize = 20; // 가로 크기

	std::vector<ETile> _tiles;

	Position _minPosition = { 0, 0 };
	Position _maxPosition = { 0, 0 };
	int32_t _spawnedFoodCount = 0;
	float _moveSpeed = 0.5f;
};
