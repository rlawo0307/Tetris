#include <iostream>
#include <string>
#include "Command.h"
#include "Class.h"
#include "Func.h"
#include <windows.h> // Sleep()
#include <conio.h> // _kbhit(),_getch(0

void Show_Option()
{
	system("cls");
	File_Open(OPTION_SCREEN_PATH);
}

void Show_Rank()
{
	system("cls");
	File_Open(RANKING_SCREEN_PATH);
}

void Show_Help()
{
	system("cls");
	File_Open(HELP_SCREEN_PATH);
}

void New_Game()
{
	std::string str;

	system("cls");
	std::cout << "1P or 2P? : ";
	std::cin >> str;
	std::cout << str[0] << std::endl;
	if (str == "1P")
	{
		Player player1 = Player();
		Play_Game_1P(player1);
	}
	else
	{
		Player player1 = Player();
		Player player2 = Player();
		Play_Game_2P(player1, player2);
	}
}

void Load_Game()
{
	//select 1p or 2p
	//input ID
	//Data Load
	//Play_Game_1P() or Play_Game_2P()
}

void Play_Game_1P(Player& p1)
{
	double speed = 1000 * p1.data.falling_speed;
	char key = ' ';

	system("cls");
	std::cout << "1P Start\n";
	File_Open(GAMEBOX_1P_PATH);

	while (1)
	{
		int block_x = BLOCK_X, block_y = BLOCK_Y;
		p1.data.Rand_Next_Block();
		p1.data.Print_Board();
		while(1)
		{
			int j = 0;
			while (j++ < 10)
			{
				Sleep(speed/10);
				if (_kbhit()) //while user not input key, game continue
				{
					key = _getch();
					switch(key)
					{
					case 80: if (p1.data.Check_Next_Line(block_x, block_y))p1.data.Change_Board(&block_x, &block_y, key); break;
					case 75: break;
					case 77: break;
					//sapce
					}
				}
			}
			if (p1.data.Check_Next_Line(block_x, block_y))
				p1.data.Change_Board(&block_x, &block_y, 80); // down
			else
				break;
		}
		if(p1.data.Check_Game_Over(block_x, block_y))
		{
			std::cout << "Game Over\n";
			break;
		}
	}
}

void Play_Game_2P(Player& p1, Player& p2)
{
	system("cls");
	std::cout << "2P Start\n";
	File_Open(GAMEBOX_2P_PATH);
}