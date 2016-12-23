#include "Game.h"

#include "Console.h"
#include <iostream>
#include <algorithm>

#include "BattleShip.h"

#define LEVEL_XOFF 3
#define LEVEL_YOFF 3

bool CGame::SaveMatch()
{
	return false;
}

void CGame::DrawIntro()
{
	// draw image background
	float b = 13, m = 80, w = 0;
	for (int i = 0; i < 20; ++i)
	{
		float inorm = (i + 1) / b;

		if (i < b)
			w = inorm * (m);
		else
		{
			inorm = 1 - (inorm - 1);
			w = inorm * m;
		}

		int x = (int)((m - w) / 2.0f);
		if (i < 15)
		{
			CConsole::ColorArea(x, i, (int)w, 1, CON_BG_BLUE);
		}
		else
		{
			CConsole::ColorArea(x, i, (int)w, 1, CON_BG_DARKBLUE);
		}
	}
	// draw image

	CConsole::ColorArea(41, 4, 1, 1, CON_BG_WHITE);
	CConsole::ColorArea(42, 4, 1, 1, CON_BG_DARKGREEN | CON_BG_DARKRED);
	CConsole::ColorArea(43, 4, 1, 1, CON_BG_WHITE);

	CConsole::ColorArea(42, 5, 1, 1, CON_BG_DARKGREEN | CON_BG_DARKRED);

	CConsole::ColorArea(40, 6, 5, 1, CON_BG_GRAY);

	CConsole::ColorArea(40, 7, 5, 1, CON_BG_GRAY);
	CConsole::ColorArea(40, 7, 1, 1, CON_BG_BLUE | CON_BG_DARKGREEN);
	CConsole::ColorArea(42, 7, 1, 1, CON_BG_BLUE | CON_BG_DARKGREEN);
	CConsole::ColorArea(44, 7, 1, 1, CON_BG_BLUE | CON_BG_DARKGREEN);

	CConsole::ColorArea(36, 8, 4, 1, CON_BG_DARKGREEN | CON_BG_DARKRED);
	CConsole::ColorArea(40, 8, 5, 1, CON_BG_GRAY);
	CConsole::ColorArea(45, 8, 2, 1, CON_BG_DARKGREEN | CON_BG_DARKRED);

	CConsole::ColorArea(17, 9, 4, 1, 0);

	CConsole::ColorArea(37, 9, 9, 1, CON_BG_GRAY);

	CConsole::ColorArea(21, 10, 4, 1, 0);

	CConsole::ColorArea(37, 10, 11, 1, CON_BG_GRAY);
	CConsole::ColorArea(37, 10, 1, 1, CON_BG_BLUE | CON_BG_DARKGREEN);
	CConsole::ColorArea(39, 10, 1, 1, CON_BG_BLUE | CON_BG_DARKGREEN);
	CConsole::ColorArea(41, 10, 1, 1, CON_BG_BLUE | CON_BG_DARKGREEN);
	CConsole::ColorArea(43, 10, 1, 1, CON_BG_BLUE | CON_BG_DARKGREEN);
	CConsole::ColorArea(45, 10, 1, 1, CON_BG_BLUE | CON_BG_DARKGREEN);
	CConsole::ColorArea(47, 10, 1, 1, CON_BG_BLUE | CON_BG_DARKGREEN);

	CConsole::ColorArea(63, 10, 4, 1, 0);

	CConsole::ColorArea(25, 11, 3, 1, 0);
	CConsole::ColorArea(28, 11, 6, 1, CON_BG_GRAY);

	CConsole::ColorArea(37, 11, 13, 1, CON_BG_GRAY);

	CConsole::ColorArea(54, 11, 6, 1, CON_BG_GRAY);
	CConsole::ColorArea(60, 11, 3, 1, 0);

	CConsole::ColorArea(16, 12, 1, 1, 0);
	CConsole::ColorArea(17, 12, 1, 1, CON_BG_GRAY);
	CConsole::ColorArea(21, 12, 1, 1, 0);
	CConsole::ColorArea(22, 12, 1, 1, CON_BG_GRAY);

	CConsole::ColorArea(28, 12, 7, 1, CON_BG_GRAY);

	CConsole::ColorArea(37, 12, 1, 1, CON_BG_BLUE | CON_BG_DARKGREEN);
	CConsole::ColorArea(38, 12, 7, 1, CON_BG_GRAY);
	CConsole::ColorArea(40, 12, 2, 1, CON_BG_DARKRED);
	CConsole::ColorArea(45, 12, 1, 1, CON_BG_BLUE | CON_BG_DARKGREEN);
	CConsole::ColorArea(46, 12, 1, 1, CON_BG_GRAY);
	CConsole::ColorArea(47, 12, 1, 1, CON_BG_BLUE | CON_BG_DARKGREEN);
	CConsole::ColorArea(48, 12, 3, 1, CON_BG_GRAY);

	CConsole::ColorArea(53, 12, 7, 1, CON_BG_GRAY);

	CConsole::ColorArea(12, 13, 50, 1, CON_BG_DARKGREEN | CON_BG_DARKRED);
	CConsole::ColorArea(12, 14, 50, 1, CON_BG_GRAY);
	CConsole::ColorArea(14, 15, 47, 1, CON_BG_GRAY);
	CConsole::ColorArea(16, 16, 44, 1, CON_BG_GRAY);

	CConsole::ColorArea(0, 20, CConsole::GetSize().x + 1, 1, CON_BG_WHITE);
	CConsole::ColorArea(0, 22, CConsole::GetSize().x + 1, 1, CON_BG_WHITE);
	CConsole::SetWriteAttribute(CON_BG_GRAY | CON_FG_RED);
	CConsole::Write(WP_CENTERX, 21, "Battle of Ships Game");
}

int CGame::DrawMenu()
{
	char* MENU_ITEMS[] = {
		"RESUME", "NEW GAME", "LOAD", "SAVE", "EXIT"
	};

	for (int i = 0; i < sizeof(MENU_ITEMS) / 4; ++i)
	{
		CConsole::ResetWriteAttribute();
		if (i == mMenuIdx)
		{
			int x = CConsole::GetSize().x / 2 - 5;
			CConsole::ColorArea(x, i + 8, 10, 1, CON_BG_GREEN);
			CConsole::SetWriteAttribute(CON_BG_GREEN);
		}

		if (i == 0 && !mGameRuns && !(mpCurShip && !mPlacmentReady))
			continue;
		else if (i == 3 && !mGameRuns)
			continue;
		else
			CConsole::Write(WP_CENTERX, i + 8, MENU_ITEMS[i]);
	}

	return 0;
}

void CGame::ProcessMenu()
{
	bool up = false;
	if (CConsole::UserInput())
	{
		CStr tmp = CConsole::Read('\0', (unsigned int)2);

		BYTE in = 0;
		if (tmp.length() == 2)
			in = (BYTE)tmp[1];
		else
			in = (BYTE)tmp[0];

		// menu down
		if (in == 80)
		{
			++mMenuIdx;
		}
		// menu up
		else if (in == 72)
		{
			up = true;
			--mMenuIdx;
		}
		else if (in == '\x1B')
		{
			if (mpCurShip && !mPlacmentReady)
			{
				mCurState = ST_PLACE;
			}
			else
			{
				mCurState = ST_RUN;
			}
		}
		// menu return
		else if (in == 13)
		{
			switch ((eMenus)mMenuIdx)
			{
			case ME_RESUME:
				if (mpCurShip && !mPlacmentReady)
				{
					mCurState = ST_PLACE;
				}
				else
				{
					mCurState = ST_RUN;
				}
				break;

			case ME_NEW:
				if (mpCurPlayer == mpPlayerOne)
				{
					mpCurShip = new CBattleShip({ 16, 9 });
					mpCurShip->Create();
				}
				else
				{
					mpCurShip = new CBattleShip({ 62, 9 });
					mpCurShip->Create();
				}

				mCurState = ST_PLACE;
				break;

			case ME_LOAD:

				break;

			case ME_SAVE:
				SaveMatch();
				break;

			case ME_EXIT:
				mRun = false;
				break;
			}
		}
	}

	if (mMenuIdx < 0)
		mMenuIdx = ME_COUNT - 1;
	else if (mMenuIdx >= ME_COUNT)
		mMenuIdx = 0;

	if (!mGameRuns && mMenuIdx == 0 && !(mpCurShip && !mPlacmentReady))
	{
		up ? --mMenuIdx : ++mMenuIdx;
	}
	else if (!mGameRuns && mMenuIdx == 3)
	{
		up ? --mMenuIdx : ++mMenuIdx;
	}
}

void CGame::ProcessUserCMD(bool* inputReady, int* hitX, int* hitY)
{
	CConsole::SetCursorPos(LEVEL_XOFF + 4, CConsole::GetSize().y - 1);

	if (CConsole::UserInput() && *inputReady)
	{
		CStr tmp = CConsole::Read('\r');

		// hit cmd
		if (mpLevel->CheckHitInRange(tmp, hitX, hitY))
		{
			mpCurPlayer->Shoot();
			*inputReady = false;
		}
		// user cmd
		else
		{
			std::transform(tmp.begin(), tmp.end(), tmp.begin(), toupper);
			if (tmp.compare("EXIT") == 0)
				mRun = false;
			else if (tmp.compare("SAVE") == 0)
				SaveMatch();
			else if (tmp.compare("\x1B") == 0)
				mCurState = ST_MENU;
		}
	}
}

void CGame::ProcessShipPlacment()
{
	bool up = false;
	if (CConsole::UserInput())
	{
		CStr tmp = CConsole::Read('\0', (unsigned int)2);

		BYTE in = 0;
		if (tmp.length() == 2)
			in = (BYTE)tmp[1];
		else
			in = (BYTE)tmp[0];

		// ship down
		if (in == 80)
		{
			mpCurShip->PosY()++;
		}
		// ship up
		else if (in == 72)
		{
			mpCurShip->PosY()--;
		}
		// ship left
		else if (in == 75)
		{
			mpCurShip->PosX()--;
		}
		// ship right
		else if (in == 77)
		{
			mpCurShip->PosX()++;
		}
		// ship turn ccw (PAGE_UP)
		if (in == 73)
		{
			mpCurShip->FlipCCW();
		}
		// ship turn cw (PAGE_DOWN)
		else if (in == 81)
		{
			mpCurShip->FlipCW();
		}
		else if (in == '\x1B')
		{
			mCurState = ST_MENU;
		}
		// make ships position fix
		else if (in == 13)
		{
			if (!mpLevel->SetShip(mpCurPlayer->WitchPlayer(), mpCurShip))
			{
				// if succeeded place the next ship

				// check if all ships are set
				// then clear the mpCurShip and set mPlacmentReady to true
			}
		}

		mpLevel->WrapShip(mpCurShip, mpCurPlayer->WitchPlayer());
	}
}

CGame::~CGame()
{
	Close();
}

bool CGame::Init()
{
	if (CConsole::Init())
		return false;

	// draw intro twice with flip between to fill both buffers
	CConsole::Clear();
	DrawIntro();
	CConsole::Flip();
	CConsole::Clear();
	DrawIntro();

	//mpPlayerOne = new CPlayer(CConsole::Read(4), 0);
	mpPlayerOne = new CPlayer("Chefkoch", HF_PL_LEFT);
	mpPlayerTwo = new CPlayer("Stefan", HF_PL_RIGHT);
	mpCurPlayer = CPlayer::Switch(mpPlayerOne, mpPlayerTwo);

	mpLevel = new CLevel({ 26,16 }, { LEVEL_XOFF,LEVEL_YOFF });

	mCurState = ST_MENU;

	// simulate the data loading and staring of the game
#define MAX_WAIT 50		// 150
	int wait = (int)MAX_WAIT;
	while (wait > 0)
	{
		float per = ((MAX_WAIT - (float)wait) / MAX_WAIT) * 100.0f;
		CConsole::Write(WP_CENTERX, 23, "%4.1f%%", per);
		CConsole::Flip({ 0,23 });
		CConsole::SleepFor(10);
		--wait;
	}

	CConsole::Clear();
	CConsole::ResetWriteAttribute();

	return true;
}

bool CGame::Run()
{
#define MAX_LOOP 20
	int loopPause = MAX_LOOP;
	int hitX = 0, hitY = 0;
	bool hit = false;
	bool inputReady = true;

	while (mRun)
	{
		// normal menu function
		if (mCurState == ST_MENU)
		{
			ProcessMenu();
		}
		// placment functions
		else if (mCurState == ST_PLACE)
		{
			ProcessShipPlacment();
		}
		// command input when game is running
		else if (mCurState == ST_RUN)
		{
			ProcessUserCMD(&inputReady, &hitX, &hitY);
		}

		// draw the game
		if (loopPause >= MAX_LOOP)
		{
			mpLevel->DrawBack();
			if (mCurState == ST_RUN)
			{
				mpLevel->DrawUI(mpPlayerOne, mpPlayerTwo);
				mpLevel->DrawContent(true);
			
				if (!inputReady && mpCurPlayer->WhoShoot() == 0)
				{
					inputReady = true;
					mpCurPlayer = CPlayer::Switch(mpPlayerOne, mpPlayerTwo);
				}

				int result = mpLevel->HitField(hitX, hitY, mpCurPlayer->WhoShoot(), &hit);
				if (result == CLevel::P_NON)
				{
					if (hit)
						mpCurPlayer->HitsSet()++;

					mpCurPlayer->ResetShoot();

					hitX = 0;
					hitY = 0;
					hit = false;
				}
			}

			if (mCurState == ST_MENU)
			{
				DrawMenu();
			}
			else if (mCurState == ST_PLACE)
			{
				mpLevel->DrawUI(mpPlayerOne, mpPlayerTwo, true);
				mpLevel->DrawContent(false, true);
				mpCurShip->Draw();
			}
			CConsole::Flip();
		}

		// pause for the draw loop
		--loopPause;
		if (loopPause < 0)
			loopPause = MAX_LOOP;

		CConsole::SleepFor(10);
	}

	return false;
}

void CGame::Close()
{
	if (mpLevel)
	{
		delete mpLevel;
		mpLevel = nullptr;
	}
	if (mpPlayerOne)
	{
		delete mpPlayerOne;
		mpPlayerOne = nullptr;
	}
	if (mpPlayerTwo)
	{
		delete mpPlayerTwo;
		mpPlayerTwo = nullptr;
	}
}


int main()
{
	CGame game;

	if (game.Init())
		game.Run();

	game.Close();

	return 0;
}