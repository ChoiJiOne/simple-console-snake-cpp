#include "GameAssert.h"
#include "MathUtils.h"
#include "LevelInfo.h"

LevelInfo::LevelInfo(int32_t level, int32_t minGoal, int32_t maxGoal, float intervalTime)
{
	GAME_CHECK(_level >= 1);
	_level = level;

	GAME_CHECK(minGoal != maxGoal);
	_minGoal = MathUtils::Min(minGoal, maxGoal);
	_maxGoal = MathUtils::Max(minGoal, maxGoal);

	GAME_CHECK(intervalTime > 0.0f);
	_intervalTime = intervalTime;
}

LevelInfo::LevelInfo(LevelInfo&& instance) noexcept
	: _level(instance._level)
	, _minGoal(instance._minGoal)
	, _maxGoal(instance._maxGoal)
	, _intervalTime(instance._intervalTime)
{
}

LevelInfo::LevelInfo(const LevelInfo& instance) noexcept
	: _level(instance._level)
	, _minGoal(instance._minGoal)
	, _maxGoal(instance._maxGoal)
	, _intervalTime(instance._intervalTime)
{
}

LevelInfo& LevelInfo::operator=(LevelInfo&& instance) noexcept
{
	if (this == &instance) return *this;

	_level = instance._level;
	_minGoal = instance._minGoal;
	_maxGoal = instance._maxGoal;
	_intervalTime = instance._intervalTime;

	return *this;
}

LevelInfo& LevelInfo::operator=(const LevelInfo& instance) noexcept
{
	if (this == &instance) return *this;

	_level = instance._level;
	_minGoal = instance._minGoal;
	_maxGoal = instance._maxGoal;
	_intervalTime = instance._intervalTime;

	return *this;
}