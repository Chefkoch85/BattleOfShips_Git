#pragma once

#include "Proj_Common.h"

class CPlayer
{
private:
	CStr mName = "";
	int mHitsSet = 0;
	bool mActive = false, mShoot = false;
	int mWhoShoot = 0;

public:
	CPlayer(crCStr name, int whoHitField);
	~CPlayer();

	cCStr GetName() { return mName; }
	bool Active() { return mActive; }
	void Shoot() { mShoot = true; }
	void ResetShoot() { mShoot = false; }
	int& HitsSet() { return mHitsSet; }
	int WhoShoot();
	int WitchPlayer() { return mWhoShoot; }

	static CPlayer* Switch(CPlayer* one, CPlayer* two);
};

