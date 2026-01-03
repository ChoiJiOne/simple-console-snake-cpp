#pragma once

#include <cstdint>

class LevelInfo
{
public:
	LevelInfo(int32_t level, int32_t minGoal, int32_t maxGoal, float intervalTime);
	LevelInfo(LevelInfo&& instance) noexcept;
	LevelInfo(const LevelInfo& instance) noexcept;

	LevelInfo& operator=(LevelInfo&& instance) noexcept;
	LevelInfo& operator=(const LevelInfo& instance) noexcept;

	const int32_t& GetLevel() const { return _level; }
	const int32_t& GetMinGoal() const { return _minGoal; }
	const int32_t& GetMaxGoal() const { return _maxGoal; }
	const float& GetIntervalTime() const { return _intervalTime; }

	bool IsGoalInRange(int goal) { return _minGoal <= goal && goal < _minGoal; }

private:
	int32_t _level = 0;
	int32_t _minGoal = 0;
	int32_t _maxGoal = 0;
	float _intervalTime = 0.0f;
};