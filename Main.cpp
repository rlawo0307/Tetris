#include <iostream>
#include <Windows.h>
#include <conio.h> //_getch()
#include "Class.h"
#include "Func.h"
#include "Command.h"

int main()
{
	char key = ' ';
	do
	{
		if (key == ' ' || key == 'o' || key == 'r' || key == 'h')
		{
			system("cls");
			File_Open(MAIN_SCREEN_PATH);
		}
		key = _getch();
		switch (key)
		{
		case 'n': New_Game(); break;
		case 'l': Load_Game(); break;
		case 'o': Show_Option(); break;
		case 'r': Show_Rank(); break;
		case 'h': Show_Help(); break;
		case 'e': break;
		}
	} while (!(key == 'n' || key == 'l'));
	return 0;
}

