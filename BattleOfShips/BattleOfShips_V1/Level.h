#pragma once

#include "Proj_Common.h"
#include "Player.h"
#include "Ship.h"
#include <vector>

class CLevel
{
public:
	enum ePhase
	{
		P_NON, P_VER, P_HOR, P_EXP, P_HIT
	};

private:
	SPos mSize;
	SPos mOffet;

	BYTE* mpFieldLeft = nullptr, *mpFieldRight = nullptr;

	void DrawField(int xoff, int yoff);
	int CheckFieldValue(int val);

	ePhase mCurHitPhase = P_NON;

public:
	CLevel(SPos size, SPos offset);
	~CLevel();

	void DrawBack();
	void DrawUI(CPlayer* one, CPlayer* two, bool noCMD = false);
	void DrawContent(bool rememberShoots = false, bool placement = false);

	void WrapShip(CShip* ship, int who);

#define HF_PL_LEFT -1
#define HF_PL_NONE 0
#define HF_PL_RIGHT 1
#define HF_ERR_POS -10
#define HF_NOSHOT -5
#define HF_NOSHIP  0x00
#define HF_SHIP	   0x01
#define HF_SHIPHIT 0x02
#define HF_NOHIT   0x04
	typedef std::vector<CShip> VEC_SHIPS;
	bool SetShip(int witch, CShip* ship);
	bool CheckHitInRange(crCStr pos, int* x, int* y);
	int HitField(int x, int y, int witch, bool* hit);
};

