#pragma once

#include <cstdint>
#include <functional>
#include <vector>

#include "Macro.h"

#include "Enum.h"

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
	void SetDirtyTile(bool isDirty) { _isDirtyTile = isDirty; }
	void SetDirtyScore(bool isDirty) { _isDirtyScore = isDirty; }
	void SetDirtyBestScore(bool isDirty) { _isDirtyBestScore = isDirty; }
	void SetSnakeResetFn(const std::function<void()>& snakeStateResetFn) { _snakeStateResetFn = snakeStateResetFn; }
	void SetGameOver(bool isGameOver) { _isGameOver = isGameOver; }

	const ETile& GetTile(int32_t x, int32_t y) const;
	const ETile& GetTile(const Position& position) const;
	const int32_t& GetRowSize() const { return _rowSize; }
	const int32_t& GetColSize() const { return _colSize; }
	const int32_t& GetSpawnedFoodCount() const { return _spawnedFoodCount; }
	const int32_t& GetCurrentScore() const { return _currentScore; }
	const int32_t& GetBestScore() const { return _bestScore; }

	bool IsDirtyTile() const { return _isDirtyTile; }
	bool IsDirtyScore() const { return _isDirtyScore; }
	bool IsDirtyBestScore() const { return _isDirtyBestScore; }
	bool IsGameOver() const { return _isGameOver; }
	bool IsValidTile(int32_t x, int32_t y) const;
	bool IsValidTile(const Position& position) const;
	bool IsOutline(int32_t x, int32_t y) const;
	bool IsOutline(const Position& position) const;
	bool HasEmptyTile() const;
	
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

private:
	Position GetRandomEmptyPosition() const;

private:
	bool _isDirtyTile = false;
	bool _isDirtyScore = false;
	bool _isDirtyBestScore = false;
	bool _isGameOver = false;

	int32_t _rowSize = 20; // 세로 크기
	int32_t _colSize = 20; // 가로 크기

	std::vector<ETile> _tiles;

	Position _minPosition = { 0, 0 };
	Position _maxPosition = { 0, 0 };

	int32_t _spawnedFoodCount = 0;

	// 점수 기준: 먹은 먹이 수
	int32_t _currentScore = 0;
	int32_t _bestScore = 0;

	// 뱀 상태 리셋
	std::function<void()> _snakeStateResetFn = nullptr;
};