#pragma once

#include <string>

typedef std::string CStr;
typedef const std::string cCStr;
typedef const std::string& crCStr;

typedef unsigned char BYTE;
typedef unsigned short WORD;

struct SPos
{
	int x, y;

	SPos() : x(0), y(0) {}
	SPos(int x, int y) : x(x), y(y) {}
};

inline bool IsBitSet(int val, int bit)
{
	return (val & bit) > 0;
}
