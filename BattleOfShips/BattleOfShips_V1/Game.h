#pragma once

#include "Player.h"
#include "Level.h"

class CGame
{
public:
	enum eState
	{
		ST_NONE,
		ST_MENU,
		ST_PLACE,
		ST_RUN
	};

	enum eMenus
	{
		ME_RESUME,
		ME_NEW,
		ME_LOAD,
		ME_SAVE,
		ME_EXIT,
		ME_COUNT
	};

private:
	CPlayer* mpPlayerOne = nullptr, *mpPlayerTwo = nullptr, *mpCurPlayer = nullptr;
	CLevel* mpLevel = nullptr;

	bool mRun = true;
	eState mCurState = ST_NONE;

	CShip* mpCurShip = nullptr;
	bool mPlacmentReady = false;

	bool SaveMatch();

	void DrawIntro();

	int mMenuIdx = 0;
	bool mGameRuns = false;
	int DrawMenu();

	void ProcessMenu();
	void ProcessUserCMD(bool* inputReady, int* hitX, int* hitY);
	void ProcessShipPlacment();

public:
	~CGame();

	bool Init();
	bool Run();
	void Close();
};

