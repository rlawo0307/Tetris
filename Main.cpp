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
		if (key == ' ' || key == 'o' || key == 'r' || key == 'h')
		{
			menu.Show_Main();
		}
		key = _getch();
		switch (key)
		{
		case 'o': menu.Show_Option(); break;
		case 'r': menu.Show_Rank(); break;
		case 'h': menu.Show_Help(); break;
		case 'n': menu.New_Game(); break;
		case 'l': menu.Load_Game(); break;
		case 'e': return 0;
		}
	} while (!(key == 'n' || key == 'l'));
}

