#include "Level.h"

#include "Console.h"

void CLevel::DrawField(int xoff, int yoff)
{
	int x = xoff, y = yoff;
	
	CConsole::Write(x, y, '\xC9');
	CConsole::Write(x + mSize.x + 1, y, '\xBB');
	CConsole::Write(x, y + mSize.y + 1, '\xC8');
	CConsole::Write(x + mSize.x + 1, y + mSize.y + 1, '\xBC');
	++x;
	// draw the top with letters (26 from left to right)
	for (char c = 'A'; c < 'A' + mSize.x; c++)
	{
		CConsole::Write(x, y, '\xCD');
		CConsole::Write(x, y - 1, c);

		CConsole::Write(x, y + mSize.y + 1, '\xCD');
		CConsole::Write(x, y + mSize.y + 2, c);

		++x;
	}

	x = xoff; y = yoff;
	// draw the left with numbers
	for (int c = 1; c < mSize.y + 1; c++)
	{
		CConsole::Write(x - 0, y + 1, '\xBA');
		CConsole::Write(x - 2, y + 1, "%2d", c);

		CConsole::Write(x + mSize.x + 1, y + 1, '\xBA');
		CConsole::Write(x + mSize.x + 2, y + 1, "%-2d", c);
		++y;
	}

	// draw water
	bool dark = false;
	for (int yw = yoff + 1; yw < mSize.y + yoff + 1; ++yw)
	{
		for (int xw = xoff + 1; xw < mSize.x + xoff + 1; ++xw)
		{
			if (dark)
				CConsole::ColorArea(xw, yw, 1, 1, CON_BG_DARKBLUE);
			else
				CConsole::ColorArea(xw, yw, 1, 1, CON_BG_BLUE);

			dark = !dark;
		}
		dark = !dark;
	}
}

int CLevel::CheckFieldValue(int val)
{
	return 0;
}

CLevel::CLevel(SPos size, SPos offset) : mSize(size), mOffet(offset)
{
	mpFieldLeft = new BYTE[mSize.x * mSize.y];
	memset(mpFieldLeft, 0, mSize.x * mSize.y);
	mpFieldRight = new BYTE[mSize.x * mSize.y];
	memset(mpFieldRight, 0, mSize.x * mSize.y);
}


CLevel::~CLevel()
{
	if (mpFieldLeft)
	{
		delete[] mpFieldLeft;
		mpFieldLeft = nullptr;
	}
	if (mpFieldRight)
	{
		delete[] mpFieldRight;
		mpFieldRight = nullptr;
	}
}

void CLevel::DrawBack()
{
	if (mSize.x > 26)
		return;

	DrawField(mOffet.x, mOffet.y);
	int x = CConsole::GetSize().x - mSize.x - 1;
	DrawField(x - mOffet.x, mOffet.y);
}

void CLevel::DrawUI(CPlayer * one, CPlayer * two, bool noCMD)
{
	int x = mOffet.x, y = mOffet.y;
	CConsole::ResetWriteAttribute();
	
	if (one->Active())
		CConsole::SetWriteAttribute(CON_FG_GREEN);
	CConsole::Write(x + 1, y - 2, one->GetName().c_str());
	CConsole::Write(x + mSize.x - 2, y - 2, "%3d", one->HitsSet());

	CConsole::ResetWriteAttribute();

	int xp2 = CConsole::GetSize().x - two->GetName().length();
	if (two->Active())
		CConsole::SetWriteAttribute(CON_FG_GREEN);
	CConsole::Write(xp2 - x, y - 2, two->GetName().c_str());
	CConsole::Write(CConsole::GetSize().x - mSize.x - x, y - 2, "%-3d", two->HitsSet());

	if (!noCMD)
	{
		CConsole::SetWriteAttribute(CON_FG_YELLOW);
		CConsole::Write(x, CConsole::GetSize().y - 1, "CMD: ");

		CConsole::SetWriteAttribute(CON_BG_GRAY | CON_FG_DARKRED);
		CConsole::ColorArea(CConsole::GetSize().x - 30, CConsole::GetSize().y - 2, 28, 1, CON_BG_GRAY);
		CConsole::ColorArea(CConsole::GetSize().x - 25, CConsole::GetSize().y - 1, 23, 2, CON_BG_GRAY);
		CConsole::Write(CConsole::GetSize().x - 29, CConsole::GetSize().y - 2, "CMD: coords (i.e. A3)");
		CConsole::Write(CConsole::GetSize().x - 24, CConsole::GetSize().y - 1, "exit");
		CConsole::Write(CConsole::GetSize().x - 24, CConsole::GetSize().y - 0, "save");
	}
	else
	{
		CConsole::SetWriteAttribute(CON_FG_YELLOW);
		CConsole::Write(WP_CENTERX, CConsole::GetSize().y - 1, "Placement mode!");
	}

	CConsole::ResetWriteAttribute();
}

void CLevel::DrawContent(bool rememberShoots, bool placement)
{
	int offsetRight = CConsole::GetSize().x - mSize.x - mOffet.x - 4;
	int xoff = mOffet.x + 1, yoff = mOffet.y + 1;
	for (int y = 0; y < mSize.y; ++y)
	{
		for (int x = 0; x < mSize.x; ++x)
		{
			int idx = x + y * mSize.x;
			BYTE left = mpFieldLeft[idx];
			BYTE right = mpFieldRight[idx];

			WORD attrMiss = CON_FG_WHITE;
			if (y % 2 == 0)
			{
				attrMiss |= (x % 2 == 0 ? CON_BG_BLUE : CON_BG_DARKBLUE);
			}
			else
			{
				attrMiss |= (x % 2 == 1 ? CON_BG_BLUE : CON_BG_DARKBLUE);
			}

			if (rememberShoots && IsBitSet(left, HF_NOHIT))
			{
				CConsole::SetWriteAttribute(attrMiss);
				CConsole::Write(x + xoff, y + yoff, 'O');
			}
			else if (IsBitSet(left, HF_SHIPHIT))
			{
				CConsole::SetWriteAttribute(CON_BG_DARKRED | CON_FG_WHITE);
				CConsole::Write(x + xoff, y + yoff, 'X');
			}
			else if (placement && IsBitSet(left, HF_SHIP))
			{
				CConsole::ColorArea(x + xoff, y + yoff, 1, 1, CON_BG_GREEN);
			}
			CConsole::ResetWriteAttribute();

			if (rememberShoots && IsBitSet(right, HF_NOHIT))
			{
				CConsole::SetWriteAttribute(attrMiss);
				CConsole::Write(x + xoff + offsetRight, y + yoff, 'O');
			}
			else if (IsBitSet(right, HF_SHIPHIT))
			{
				CConsole::SetWriteAttribute(CON_BG_DARKRED | CON_FG_WHITE);
				CConsole::Write(x + xoff + offsetRight, y + yoff, 'X');
			}
			else if (placement && IsBitSet(right, HF_SHIP))
			{
				CConsole::ColorArea(x + xoff + offsetRight, y + yoff, 1, 1, CON_BG_GREEN);
			}
			CConsole::ResetWriteAttribute();
		}
	}
}

void CLevel::WrapShip(CShip * ship, int who)
{
	if (who == HF_PL_NONE)
		return;

	int bl = 0, br = 0, bt = 0, bb = 0;

	if (who == HF_PL_LEFT)
	{
		bl = mOffet.x + 1;
		br = bl + mSize.x;
		bt = mOffet.y + 1;
		bb = bt + mSize.y;
	}
	else if (who == HF_PL_RIGHT)
	{
		int cw = CConsole::GetSize().x;
		bl = cw - mOffet.x - mSize.x;
		br = bl + mSize.x;
		bt = mOffet.y + 1;
		bb = bt + mSize.y;
	}

	if (ship->PosX() < bl)
		ship->PosX() = bl;
	else if (ship->PosX() + ship->GetSize().x > br)
		ship->PosX() = br - ship->GetSize().x;

	if (ship->PosY() < bt)
		ship->PosY() = bt;
	else if (ship->PosY() + ship->GetSize().y > bb)
		ship->PosY() = bb - ship->GetSize().y;
}

bool CLevel::SetShip(int witch, CShip* ship)
{
	if (witch == HF_PL_NONE)
		return true;

	bool error = false;
	// check for placment error
	for (int y = 0; y < ship->GetSize().y; ++y)
	{
		for (int x = 0; x < ship->GetSize().x; ++x)
		{
			if (ship->IsShape(x, y))
			{
				int xf = ship->GetPos().x - mOffet.x - 1;
				int yf = ship->GetPos().y - mOffet.y - 1;

				xf += x;
				yf += y;

				if (witch == HF_PL_LEFT)
				{
					if (mpFieldLeft[xf + yf * mSize.x] != 0)
					{
						// error when placing
						return true;
					}
				}
				else if (witch == HF_PL_RIGHT)
				{
					if (mpFieldRight[xf + yf * mSize.x] != 0)
					{
						// error when placing
						return true;
					}
				}
			}
		}
	}

	// place if no error
	for (int y = 0; y < ship->GetSize().y; ++y)
	{
		for (int x = 0; x < ship->GetSize().x; ++x)
		{
			if (ship->IsShape(x, y))
			{
				int xf = ship->GetPos().x - mOffet.x - 1;
				int yf = ship->GetPos().y - mOffet.y - 1;

				xf += x;
				yf += y;

				if (witch == HF_PL_LEFT)
				{
					mpFieldLeft[xf + yf * mSize.x] = HF_SHIP;
				}
				else if (witch == HF_PL_RIGHT)
				{
					mpFieldRight[xf + yf * mSize.x] = HF_SHIP;
				}
			}
		}
	}

	return false;
}

bool CLevel::CheckHitInRange(crCStr pos, int * x, int * y)
{
	if (pos.length() < 2 || pos.length() > 3)
		return false;

	char col = pos.substr(0, 1)[0];
	col = toupper(col);
	CStr row = pos.substr(1);
	int rowNum = atoi(row.c_str()) - 1;

	int xt = -1, yt = -1;

	if (col >= 'A' && col <= mSize.x + 'A')
		xt = col - 'A';
	if (rowNum >= 0 && rowNum < mSize.y)
		yt = rowNum;

	if (xt < 0 || yt < 0)
		return false;

	*x = xt;
	*y = yt;

	return true;
}

int CLevel::HitField(int x, int y, int witch, bool* hit)
{
	if (x < 0 || x >= mSize.x ||
		y < 0 || y >= mSize.y)
		return HF_ERR_POS;

	if (witch == 0)
		return HF_NOSHOT;

	CStr f = "FIRING";
	int xf = (CConsole::GetSize().x - f.length()) / 2;
	CConsole::SetWriteAttribute(CON_FG_RED | CON_FG_GREEN);
	CConsole::Write(xf, 2, f.c_str());
	CConsole::ResetWriteAttribute();

	int offsetRight = (witch == HF_PL_LEFT ? CConsole::GetSize().x - mSize.x - mOffet.x - 4: 0);

	int xh = x + mOffet.x + 1 + offsetRight;
	int yh = y + mOffet.y + 1;
	switch (mCurHitPhase)
	{
	case CLevel::P_NON:
		mCurHitPhase = P_VER;
		break;
	case CLevel::P_VER:
		// phase one draw line top->bottom
		mCurHitPhase = P_HOR;

		CConsole::ColorArea(xh, mOffet.y + 1, 1, mSize.y, CON_BG_GREEN | CON_BG_RED);

		break;

	case CLevel::P_HOR:
		// phase two draw line left->right
		mCurHitPhase = P_EXP;

		CConsole::ColorArea(xh, mOffet.y + 1, 1, mSize.y, CON_BG_GREEN | CON_BG_RED);
		CConsole::ColorArea(mOffet.x + 1 + offsetRight, yh, mSize.x, 1, CON_BG_GREEN | CON_BG_RED);

		break;

	case CLevel::P_EXP:
		// phase three draw red explision
		mCurHitPhase = P_HIT;

		CConsole::ColorArea(xh, mOffet.y + 1, 1, mSize.y, CON_BG_GREEN | CON_BG_RED);
		CConsole::ColorArea(mOffet.x + 1 + offsetRight, yh, mSize.x, 1, CON_BG_GREEN | CON_BG_RED);
		CConsole::ColorArea(xh, yh, 1, 1, CON_BG_RED);
		break;

	case CLevel::P_HIT:
	{
		// phase four draw red or yellow box for hit feedback
		mCurHitPhase = P_NON;

		CConsole::ColorArea(xh, yh, 1, 1, CON_BG_RED);

		int idx = x + y * mSize.x;
		if (witch == HF_PL_LEFT)
		{
			if (mpFieldRight[idx] == HF_SHIP)
				mpFieldRight[idx] |= HF_SHIPHIT;
			else
				mpFieldRight[idx] = HF_NOHIT;
		}
		else
		{
			if (mpFieldLeft[idx] == HF_SHIP)
				mpFieldLeft[idx] |= HF_SHIPHIT;
			else
				mpFieldLeft[idx] = HF_NOHIT;
		}

		break;
	}
	default:
		break;
	}
	
	return (int)mCurHitPhase;
}
