#pragma once

#include "Ship.h"

class CBattleShip :	public CShip
{
public:
	CBattleShip();
	CBattleShip(const SPos& pos) : CShip(pos) {}
	~CBattleShip();

	// Geerbt �ber CShip
	virtual void Create() override;
};

