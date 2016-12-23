#pragma once

#include "Proj_Common.h"

class CShip
{
protected:
	SPos mSize, mPos;
	BYTE** mShape = nullptr;

public:
	CShip() {}
	CShip(const SPos& pos);
	virtual ~CShip();

	virtual void Create() = 0;

	void SetPos(const SPos& pos) { mPos = pos; }
	int& PosX() { return mPos.x; }
	int& PosY() { return mPos.y; }
	SPos GetPos() { return mPos; }
	SPos GetSize() { return mSize; }
	bool IsShape(int x, int y) { return mShape[y][x] > 0; }
	void Draw();

	void FlipCW();
	void FlipCCW();
};

