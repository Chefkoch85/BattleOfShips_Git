#pragma once

#include "Ship.h"

class CBattleShip :	public CShip
{
public:
	CBattleShip();
	CBattleShip(const SPos& pos) : CShip(pos) {}
	~CBattleShip();

	// Geerbt über CShip
	virtual void Create() override;
};

