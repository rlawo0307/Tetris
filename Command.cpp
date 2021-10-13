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
		Player player1 = Player(1);
		Play_1P(player1);
	}
	else
	{
		Player player1 = Player(1);
		Player player2 = Player(2);
		Play_2P(player1, player2);
	}
}

void Load_Game()
{
	//select 1p or 2p
	//input ID
	//Data Load
	//Play_Game_1P() or Play_Game_2P()
}

void Play_1P(Player& p1)
{
	int box_x, box_y;
	system("cls");
	//File_Open(GAMEBOX_1P_PATH);

	Play_Game(p1);
}

void Play_2P(Player& p1, Player& p2)
{
	system("cls");
	//File_Open(GAMEBOX_2P_PATH);
}

void Play_Game(Player& player)
{
	double speed = player.gm.Cal_Speed();
	char key = ' ';

	system("cls");
	//File_Open(GAMEBOX_1P_PATH);

	while (player.gm.Game_Over())
	{
		int block_x = BLOCK_X, block_y = BLOCK_Y;
		player.gm.Rand_Next_Block();

		while (1)
		{
			int j = 0;
			while (j++ < 10)
			{
				Sleep(speed / 10);
				if (_kbhit()) //while user not input key, game continue
				{
					key = _getch();
					switch (key)
					{
					case 72: while (player.gm.Check_Next_Line(block_x, block_y)) player.gm.Change_Board(&block_x, &block_y, 80); break;
					case 80: if (player.gm.Check_Next_Line(block_x, block_y)) player.gm.Change_Board(&block_x, &block_y, key); break;
					case 75: if (player.gm.Check_Left_Side(block_x, block_y)) player.gm.Change_Board(&block_x, &block_y, key); break;
					case 77: if (player.gm.Check_Right_Side(block_x, block_y)) player.gm.Change_Board(&block_x, &block_y, key); break;
						//sapce
					}
				}
			}
			if (player.gm.Check_Next_Line(block_x, block_y))
			{
				player.gm.Change_Board(&block_x, &block_y, 80); // down
				Sleep(speed);
			}
			else
			{
				player.gm.Updata_Top();
				player.gm.Score_Check(&block_x, &block_y);
				break;
			}
		}
	}
	std::cout << "Game Over\n";
}