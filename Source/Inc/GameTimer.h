#pragma once

#include <cstdint>

class GameTimer
{
public:
	GameTimer();
	GameTimer(GameTimer&& instance) noexcept;
	GameTimer(const GameTimer& instance) noexcept;
	virtual ~GameTimer() = default;

	float GetTotalSeconds() const;
	float GetDeltaSeconds() const;

	void Reset();
	void Start();
	void Stop();
	void Tick();

private:
	double _secondsPerCount = 0.0;
	double _deltaTime = 0.0;

	int64_t _baseTime = 0LL;
	int64_t _pausedTime = 0LL;
	int64_t _stopTime = 0LL;
	int64_t _prevTime = 0LL;
	int64_t _currTime = 0LL;

	bool _bIsStopped = false;
};