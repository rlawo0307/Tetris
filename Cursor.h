#pragma once

#include <windows.h>

class Cursor
{
private:
	COORD Cur;

public:
	void Cursor_Move(int x, int y)
	{
		Cur.X = x;
		Cur.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	}
};