#include "Console.h"

#include <iostream>

#include <Windows.h>
#include <conio.h>

HANDLE CConsole::mhConsole = nullptr;
HANDLE CConsole::mhBackBuffer = nullptr;
HANDLE CConsole::mhCurBackBuffer = nullptr;
SPos CConsole::mcSize = {};
int CConsole::mCursorHieght = 10;

void CConsole::Write(const char * fmt, va_list args)
{
	//vprintf(fmt, args);

	DWORD written = 0;
	char buff[512] = { 0 };
	vsprintf_s(buff, fmt, args);

	WriteConsoleA(mhCurBackBuffer, buff, strlen(buff), &written, nullptr);
}

CConsole::CConsole()
{
}


CConsole::~CConsole()
{
	if (mhBackBuffer)
		CloseHandle(mhBackBuffer);
}

bool CConsole::Init()
{
	mcSize.x = 80;
	mcSize.y = 25;

	mhConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!mhConsole)
		return true;

	return SetSize(mcSize.x, mcSize.y);
}

bool CConsole::Init(short w, short h)
{
	if (Init())
		return true;

	return SetSize(w, h);
}

void CConsole::Clear()
{
	COORD topLeft = { 0, 0 };
	DWORD written = 0;

	FillConsoleOutputCharacterA(
		mhCurBackBuffer,
		' ',
		(mcSize.x + 1) * (mcSize.y + 1),
		topLeft,
		&written
		);
	FillConsoleOutputAttribute(
		mhCurBackBuffer,
		FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		(mcSize.x + 1) * (mcSize.y + 1),
		topLeft,
		&written
		);

	ResetWriteAttribute();
}

void CConsole::Reset()
{
	SetCursorPos(0, 0);
}

void CConsole::Flip(SPos toResetTo)
{
	CONSOLE_CURSOR_INFO ci = { 0 };
	ci.bVisible = false;
	ci.dwSize = mCursorHieght;

	if (mhBackBuffer == mhCurBackBuffer)
	{
		ci.bVisible = true;
		if (!SetConsoleCursorInfo(mhBackBuffer, &ci))
		{
			DWORD e = GetLastError();
			int a = 0;
		}
		SetConsoleActiveScreenBuffer(mhBackBuffer);
		mhCurBackBuffer = mhConsole;
	}
	else
	{
		ci.bVisible = true;
		if (!SetConsoleCursorInfo(mhConsole, &ci))
		{
			DWORD e = GetLastError();
			int a = 0;
		}
		SetConsoleActiveScreenBuffer(mhConsole);
		mhCurBackBuffer = mhBackBuffer;
	}

	if (toResetTo.x >= 0 && toResetTo.y >= 0)
	{
		SetCursorPos(toResetTo.x, toResetTo.y);
	}
	else
	{
		Clear();
	}

	ci.bVisible = false;
	if (!SetConsoleCursorInfo(mhCurBackBuffer, &ci))
	{
		DWORD e = GetLastError();
		int a = 0;
	}
}

void CConsole::SleepFor(int ms)
{
	Sleep(ms);
}

bool CConsole::UserInput()
{
	return _kbhit() > 0;
}

void CConsole::SetCursorPos(short x, short y)
{
	if (x < 0)
		x = 0;
	else if (x > mcSize.x)
		x = mcSize.x;

	if (y < 0)
		y = 0;
	else if (y > mcSize.y)
		y = mcSize.y;

	COORD c = { x,y };
	SetConsoleCursorPosition(mhConsole, c);
	SetConsoleCursorPosition(mhBackBuffer, c);
}

SPos CConsole::GetCursorPos()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };
	GetConsoleScreenBufferInfo(mhConsole, &csbi);
	SPos c = { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };
	return c;
}

bool CConsole::SetSize(short w, short h)
{
	mcSize.x = w;
	mcSize.y = h;

	SMALL_RECT sr = { (short)0, (short)0, (short)(mcSize.x - 1), (short)(mcSize.y - 1) };
	if (!SetConsoleWindowInfo(mhConsole, true, &sr))
	{
		DWORD e = GetLastError();
		return true;
	}

	COORD c = { (short)mcSize.x, (short)mcSize.y };
	if (!SetConsoleScreenBufferSize(mhConsole, c))
	{
		DWORD e = GetLastError();
		return true;
	}

	if (!mhBackBuffer)
	{
		mhBackBuffer = CreateConsoleScreenBuffer(GENERIC_WRITE,
			0,
			nullptr,
			CONSOLE_TEXTMODE_BUFFER,
			nullptr);

		if (!mhBackBuffer)
		{
			DWORD e = GetLastError();
			return true;
		}

		if (!SetConsoleScreenBufferSize(mhBackBuffer, c))
		{
			DWORD e = GetLastError();
			return true;
		}
	}

	mhCurBackBuffer = mhBackBuffer;

	mcSize.x -= 1;
	mcSize.y -= 1;
	return false;
}

void CConsole::SetWriteAttribute(WORD attr)
{
	SetConsoleTextAttribute(mhCurBackBuffer, attr);
}

void CConsole::ResetWriteAttribute()
{
	SetWriteAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void CConsole::ColorArea(short x, short y, short w, short h, WORD attr)
{
	COORD topLeft = { x, y };
	DWORD written = 0;

	for (int i = 0; i < h; ++i)
	{
		FillConsoleOutputAttribute(
			mhCurBackBuffer,
			attr,
			w,
			topLeft,
			&written
			);

		++topLeft.Y;
	}
}

void CConsole::Write(short x, short y, const char * fmt, ...)
{
	char buff[512] = { 0 };

	short nx = x;
	const char* str = fmt;

	va_list args;
	va_start(args, fmt);
	if (x < 0)
	{
		vsprintf_s(buff, fmt, args);

		switch (nx)
		{
		case -1:
			nx = (short)(mcSize.x - strlen(buff)) / 2;
			break;

		case -2:
			nx = (short)(mcSize.x - strlen(buff));
			break;
		}
	}

	// set pos
	SetCursorPos(nx, y);

	// write at pos
	Write(str, args);
	va_end(args);
}

void CConsole::Write(short x, short y, char c)
{
	// set pos
	SetCursorPos(x, y);

	// write at pos
	va_list args;
	va_start(args, y);

	Write("%c", args);
	va_end(args);
}

cCStr CConsole::Read(char finish, unsigned int maxSize)
{
	//char buffer[256] = { 0 };
	//DWORD read = 0;
	//ReadConsoleA(mhCurBackBuffer, buffer, 255, &read, nullptr);

	// TODO: check the abilty to read mouse events
	// to look further "winapi:low level console input"
	//INPUT_RECORD ir = { 0 };
	//DWORD read = 0;
	//if (mhBackBuffer == mhCurBackBuffer)
	//	ReadConsoleInputA(mhConsole, &ir, 1, &read);
	//else
	//	ReadConsoleInputA(mhBackBuffer, &ir, 1, &read);

	SPos curPos = GetCursorPos();
	CStr temp;
	char c = 0;
	bool noOut = false;
	while ((c = _getch()) != finish && temp.length() < maxSize)
	{
		temp += c;
		if (c == -32 || c == '\r' || '\x1B')
			noOut = true;

		if (!noOut)
		{
			SetCursorPos(curPos.x, curPos.y);

			DWORD written = 0;
			if (mhBackBuffer == mhCurBackBuffer)
				WriteConsoleA(mhConsole, temp.c_str(), temp.length(), &written, nullptr);
			else
				WriteConsoleA(mhBackBuffer, temp.c_str(), temp.length(), &written, nullptr);
		}

		if (temp.length() >= maxSize || c == '\r' || c == '\x1B')
			break;
	}
	return temp;
}

cCStr CConsole::Read(unsigned int maxSize)
{
	return Read('\r', maxSize);
}

cCStr CConsole::Read(char finish)
{
	return Read(finish, 255);
}
