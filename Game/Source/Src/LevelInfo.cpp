#include "GenericAssert.h"
#include "MathUtils.h"

#include "LevelInfo.h"

LevelInfo::LevelInfo(int32_t level, int32_t minScore, int32_t maxScore, float intervalTime)
{
	CHECK(level >= 1);
	_level = level;

	CHECK(minScore != maxScore);
	_minScore = MathUtils::Min(minScore, maxScore);
	_maxScore = MathUtils::Max(minScore, maxScore);

	CHECK(intervalTime > 0.0f);
	_intervalTime = intervalTime;
}

LevelInfo::LevelInfo(LevelInfo&& instance) noexcept
	: _level(instance._level)
	, _minScore(instance._minScore)
	, _maxScore(instance._maxScore)
	, _intervalTime(instance._intervalTime)
{
}

LevelInfo::LevelInfo(const LevelInfo& instance) noexcept
	: _level(instance._level)
	, _minScore(instance._minScore)
	, _maxScore(instance._maxScore)
	, _intervalTime(instance._intervalTime)
{
}

LevelInfo& LevelInfo::operator=(LevelInfo&& instance) noexcept
{
	if (this == &instance) return *this;

	_level = instance._level;
	_minScore = instance._minScore;
	_maxScore = instance._maxScore;
	_intervalTime = instance._intervalTime;

	return *this;
}

LevelInfo& LevelInfo::operator=(const LevelInfo& instance) noexcept
{
	if (this == &instance) return *this;

	_level = instance._level;
	_minScore = instance._minScore;
	_maxScore = instance._maxScore;
	_intervalTime = instance._intervalTime;

	return *this;
}

EScoreState LevelInfo::GetScoreState(int32_t score) const
{
	if (score < _minScore)
	{
		return EScoreState::BELOW_MIN;
	}
	else if (_minScore <= score && score < _maxScore)
	{
		return EScoreState::IN_RANGE;
	}
	else
	{
		return EScoreState::ABOVE_MAX;
	}
}