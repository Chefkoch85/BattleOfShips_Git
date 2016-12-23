#include "BattleShip.h"



CBattleShip::CBattleShip()
{
}


CBattleShip::~CBattleShip()
{
}

void CBattleShip::Create()
{
	mSize.x = 3;
	mSize.y = 5;

	mShape = new BYTE*[mSize.y];
	for (int i = 0; i < mSize.y; ++i)
	{
		mShape[i] = new BYTE[mSize.x];
		memset(mShape[i], 0, mSize.x);
	}

	int x = 1, y = 0;
	mShape[y][x] = 1;
	x = 1; y = 1;
	mShape[y][x] = 1;
	x = 0; y = 2;
	mShape[y][x] = 1;
	x = 1; y = 2;
	mShape[y][x] = 1;
	x = 2; y = 2;
	mShape[y][x] = 1;
	x = 0; y = 3;
	mShape[y][x] = 1;
	x = 1; y = 3;
	mShape[y][x] = 1;
	x = 2; y = 3;
	mShape[y][x] = 1;
	x = 1; y = 4;
	mShape[y][x] = 1;
}
