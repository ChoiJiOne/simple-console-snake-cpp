#include "GameTimer.h"
#include "WindowsAssert.h"

GameTimer::GameTimer()
	: _secondsPerCount(0.0)
	, _deltaTime(-1.0)
	, _baseTime(0)
	, _pausedTime(0)
	, _prevTime(0)
	, _currTime(0)
	, _bIsStopped(false)
{
	int64_t countsPerSec = 0LL;
	WINDOWS_CHECK(QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSec)));
	_secondsPerCount = 1.0 / static_cast<double>(countsPerSec);
}

GameTimer::GameTimer(GameTimer&& instance) noexcept
	: _secondsPerCount(instance._secondsPerCount)
	, _deltaTime(instance._deltaTime)
	, _baseTime(instance._baseTime)
	, _pausedTime(instance._pausedTime)
	, _prevTime(instance._prevTime)
	, _currTime(instance._currTime)
	, _bIsStopped(instance._bIsStopped) {}

GameTimer::GameTimer(const GameTimer& instance) noexcept
	: _secondsPerCount(instance._secondsPerCount)
	, _deltaTime(instance._deltaTime)
	, _baseTime(instance._baseTime)
	, _pausedTime(instance._pausedTime)
	, _prevTime(instance._prevTime)
	, _currTime(instance._currTime)
	, _bIsStopped(instance._bIsStopped) {}

float GameTimer::GetTotalSeconds() const
{
	if (_bIsStopped)
	{
		return static_cast<float>(((_stopTime - _pausedTime) - _baseTime) * _secondsPerCount);
	}
	else
	{
		return static_cast<float>(((_currTime - _pausedTime) - _baseTime) * _secondsPerCount);
	}
}

float GameTimer::GetDeltaSeconds() const
{
	return static_cast<float>(_deltaTime);
}

void GameTimer::Reset()
{
	int64_t currTime = 0LL;
	WINDOWS_CHECK(QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime)));

	_baseTime = currTime;
	_prevTime = currTime;
	_stopTime = 0;
	_bIsStopped = false;
}

void GameTimer::Start()
{
	if (!_bIsStopped)
	{
		return;
	}

	int64_t startTime = 0LL;
	WINDOWS_CHECK(QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime)));

	_pausedTime += (startTime - _stopTime);

	_prevTime = startTime;
	_stopTime = 0;
	_bIsStopped = false;
}

void GameTimer::Stop()
{
	if (_bIsStopped)
	{
		return;
	}

	int64_t currTime = 0LL;
	WINDOWS_CHECK(QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime)));

	_stopTime = currTime;
	_bIsStopped = true;
}

void GameTimer::Tick()
{
	if (_bIsStopped)
	{
		_deltaTime = 0.0;
		return;
	}

	int64_t currTime = 0LL;
	WINDOWS_CHECK(QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime)));
	_currTime = currTime;

	_deltaTime = (_currTime - _prevTime) * _secondsPerCount;
	_prevTime = _currTime;

	if (_deltaTime < 0.0)
	{
		_deltaTime = 0.0;
	}
}