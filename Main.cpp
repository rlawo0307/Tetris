#include <iostream>
#include <Windows.h>
#include <conio.h> //_getch()
#include "Menu.h"

int main()
{
	MENU menu = MENU();
	char key = ' ';

	do
	{
		menu.Show_Main();
		key = _getch();
		switch (key)
		{
		case 'n': menu.New_Game(); break;
		case 'l': menu.Load_Game(); break;
		case 'h': menu.Show_Help(); break;
		case 'r': menu.Show_Rank(); break;
		case 'o': menu.Show_Option(); break;
		case 'e': return 0;
		}
	} while (key != 'l');
}

