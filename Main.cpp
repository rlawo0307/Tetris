#include <iostream>
#include <Windows.h>
#include <conio.h> //_getch()
#include "Class.h"
#include "Func.h"
#include "Command.h"

void Test();

int main()
{

	//Test();
	Player player1 = Player();
	Play_Game_1P(player1);

	/*
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
	*/

	return 0;
}

void Test()
{
	int cur_block[BLOCK_COL][BLOCK_ROW];

	for (int i_next_block = 0; i_next_block <= 7; i_next_block++)
	{
		memset(cur_block, C_EMPTY, sizeof(cur_block));

		switch (i_next_block)
		{
		case 1: cur_block[0][0] = cur_block[1][0] = cur_block[2][0] = cur_block[3][0] = i_next_block; break;
		case 2: cur_block[2][3] = cur_block[3][1] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		case 3: cur_block[2][1] = cur_block[3][1] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		case 4: cur_block[2][2] = cur_block[3][1] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		case 5: cur_block[2][2] = cur_block[2][3] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		case 6: cur_block[2][2] = cur_block[2][3] = cur_block[3][1] = cur_block[3][2] = i_next_block; break;
		case 7: cur_block[2][1] = cur_block[2][2] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		}

		std::cout << "dd\n";

		for (int i = 0; i < BLOCK_COL; i++)
		{
			for (int j = 0; j < BLOCK_ROW; j++)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cur_block[i][j]);
				std::cout << "бс";
			}
			std::cout << std::endl;
		}
		std::cout << "dd\n";
	}
}
