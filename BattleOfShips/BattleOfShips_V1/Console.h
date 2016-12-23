#pragma once

#include "Proj_Common.h"

#define CON_FG_DARKBLUE  0x0001 // text color contains blue.
#define CON_FG_DARKGREEN 0x0002 // text color contains green.
#define CON_FG_DARKRED   0x0004 // text color contains red.
#define CON_FG_INTENSITY 0x0008 // text color is intensified.
#define CON_FG_BLUE		 CON_FG_DARKBLUE | CON_FG_INTENSITY
#define CON_FG_GREEN	 CON_FG_DARKGREEN | CON_FG_INTENSITY
#define CON_FG_RED		 CON_FG_DARKRED | CON_FG_INTENSITY
#define CON_FG_YELLOW	 CON_FG_RED | CON_FG_GREEN
#define CON_FG_GRAY		 CON_FG_DARKRED | CON_FG_DARKGREEN | CON_FG_DARKBLUE
#define CON_FG_WHITE	 CON_FG_RED | CON_FG_GREEN | CON_FG_BLUE | CON_FG_INTENSITY

#define CON_BG_DARKBLUE  0x0010 // background color contains blue.
#define CON_BG_DARKGREEN 0x0020 // background color contains green.
#define CON_BG_DARKRED   0x0040 // background color contains red.
#define CON_BG_INTENSITY 0x0080 // background color is intensified.
#define CON_BG_BLUE		 CON_BG_DARKBLUE | CON_BG_INTENSITY
#define CON_BG_GREEN	 CON_BG_DARKGREEN | CON_BG_INTENSITY
#define CON_BG_RED		 CON_BG_DARKRED | CON_BG_INTENSITY
#define CON_BG_YELLOW	 CON_BG_RED | CON_BG_GREEN
#define CON_BG_GRAY		 CON_BG_DARKRED | CON_BG_DARKGREEN | CON_BG_DARKBLUE
#define CON_BG_WHITE	 CON_BG_RED | CON_BG_GREEN | CON_BG_BLUE | CON_BG_INTENSITY

class CConsole
{
private:
	static void* mhConsole;
	static void* mhBackBuffer;
	static void* mhCurBackBuffer;
	static SPos mcSize;
	static int mCursorHieght;

private:
	static void Write(const char* fmt, va_list args);

public:
	CConsole();
	~CConsole();

	static bool Init();
	static bool Init(short w, short h);

	static void Clear();
	static void Reset();

	static void Flip(SPos toResetTo = { -1,-1 });

	static void SleepFor(int ms);

	static bool UserInput();

	static void SetCursorPos(short x, short y);
	static SPos GetCursorPos();
	static void SetCursorSize(int s) { mCursorHieght = s; }

	static bool SetSize(short w, short h);
	static SPos GetSize() { return mcSize; }

	static void SetWriteAttribute(WORD attr);
	static void ResetWriteAttribute();
	static void ColorArea(short x, short y, short w, short h, WORD attr);

#define WP_CENTERX -1
#define WP_RIGHT -2
	static void Write(short x, short y, const char* fmt, ...);
	static void Write(short x, short y, char c);

	static cCStr Read(char finish, unsigned int maxSize);
	static cCStr Read(unsigned int maxSize = 255);
	static cCStr Read(char finish = '\r');
};

