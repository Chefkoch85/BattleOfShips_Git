#include "Ship.h"

#include "Console.h"

CShip::CShip(const SPos& pos) : mPos(pos)
{
}


CShip::~CShip()
{
}

void CShip::Draw()
{
	for (int y = 0; y < mSize.y; ++y)
	{
		for (int x = 0; x < mSize.x; ++x)
		{
			if (mShape[y][x] == 1)
				CConsole::ColorArea(x + mPos.x, y + mPos.y, 1, 1, CON_BG_GRAY);
		}
	}
}

void CShip::FlipCW()
{
	int nw = mSize.y, nh = mSize.x;
	BYTE** tmp = new BYTE*[nh];
	for (int i = 0; i < nh; ++i)
	{
		tmp[i] = new BYTE[nw];
		memset(tmp[i], 0, nw);
	}


	for (int x = 0; x < mSize.x; x++) 
	{
		for (int y = 0; y < mSize.y; y++) 
		{
			tmp[x][y] = mShape[mSize.y - 1 - y][x];
		}
	}
	
	mSize.x = nw;
	mSize.y = nh;

	delete[] mShape;
	mShape = tmp;
}

void CShip::FlipCCW()
{
	int nw = mSize.y, nh = mSize.x;
	BYTE** tmp = new BYTE*[nh];
	for (int i = 0; i < nh; ++i)
	{
		tmp[i] = new BYTE[nw];
		memset(tmp[i], 0, nw);
	}


	for (int x = 0; x < mSize.x; x++)
	{
		for (int y = 0; y < mSize.y; y++)
		{
			tmp[x][y] = mShape[y][mSize.x - 1 - x];
		}
	}

	mSize.x = nw;
	mSize.y = nh;

	delete[] mShape;
	mShape = tmp;
}
