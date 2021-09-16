#include <iostream>
#include <string>
#include <fstream>
#include <conio.h> // _kbhit(),_getch(0
#include <windows.h>
#include "Func.h"
#include "Class.h"

void File_Open(const std::string path)
{
	std::string tmp;

	std::ifstream ifs;
	ifs.open(path);
	if (!ifs.is_open())
	{
		std::cout << "File Open Fail\n";
		return;
	}
	while (getline(ifs, tmp))
		std::cout << tmp << std::endl;
	ifs.close();
}

void Cursor::Get_Cursor()
{
	/*
	POINT cur;
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;

	while (1)
	{
		GetCursorPos(&cur);
		pos.X = cur.x;
		pos.Y = cur.y;
		std::cout << cur.x << " " << cur.y << std::endl;
		
	}
	SetConsoleCursorPosition(stdHandle, pos);
	*/
	/*
	POINT cur;
	while (1)
	{
		GetCursorPos(&cur);
		std::cout << cur.x << " " << cur.y << std::endl;
	}
	*/
	/*
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	*/
}

void Cursor::Set_Cursor()
{

}

void Cursor_Move(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}