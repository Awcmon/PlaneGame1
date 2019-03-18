#pragma once

#include <math.h>

//approach a value
inline float approach(float value, float target, float increment)
{
	if (value < target)
	{
		if ((value + increment) < target)
		{
			value += increment;
		}
		else
		{
			value = target;
		}
	}
	else if (value > target)
	{
		if ((value + increment) > target)
		{
			value -= increment;
		}
		else
		{
			value = target;
		}
	}
	else
	{
		value = target;
	}

	return value;
}

//clamp a value
inline float clamp(float value, float min, float max)
{
	if (value > max)
	{
		value = max;
	}
	else if (value < min)
	{
		value = min;
	}
	return value;
}

//normalize angle between -180 and 180 degrees
inline float normalizeAngle(float _ang)
{
	return (float)(fmod((_ang + 180.0f), 360.0f) - 180.0f);
}

//calculate normalized difference between two angles
inline float angleDifference(float a, float b)
{
	float diff = normalizeAngle(a - b);

	if (diff < 180.0f)
	{
		return diff;
	}

	return diff - 360.0f;
}

//approach an angle with the least rotation (solves the problem of -180 and 180 degrees being next to each other)
inline float ApproachAngle(float cur, float target, float inc)
{
	float diff = angleDifference(target, cur);
	return approach(cur, cur + diff, inc);
}
