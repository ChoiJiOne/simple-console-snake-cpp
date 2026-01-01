#pragma once

#include <cstdint>

class MathUtils
{
public:
	template <typename T>
	static __forceinline T Max(const T& lhs, const T& rhs)
	{
		return (lhs < rhs ? rhs : lhs);
	}

	template <typename T>
	static __forceinline T Min(const T& lhs, const T& rhs)
	{
		return (lhs < rhs ? lhs : rhs);
	}

	template <typename T>
	static __forceinline T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min<T>(upper, Max<T>(lower, value));
	}

	static int32_t GenerateRandomInt(int32_t minValue, int32_t maxValue); // [minValue, maxValue]
	static float GenerateRandomFloat(float minValue, float maxValue); // [minValue, maxValue)
};