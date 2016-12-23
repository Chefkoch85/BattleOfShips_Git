#include "Player.h"



CPlayer::CPlayer(crCStr name, int whoHitField) : mName(name), mHitsSet(0), mWhoShoot(whoHitField)
{
}


CPlayer::~CPlayer()
{
}

int CPlayer::WhoShoot()
{
	return (mShoot ? mWhoShoot : 0); 
}

CPlayer * CPlayer::Switch(CPlayer * one, CPlayer * two)
{
	if (!one->mActive && !two->mActive)
	{
		one->mActive = true;
	}
	else
	{
		one->mActive = !one->mActive;
		two->mActive = !two->mActive;
	}

	return (one->Active() ? one : two);
}

