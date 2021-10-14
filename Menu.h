#pragma once

#include <iostream>
#include "File.h"
#include "Player.h"
#include "Game_Manager.h"

#define MAIN_SCREEN_PATH "./res/main_menu.txt"
#define RANKING_SCREEN_PATH "./res/rank.txt"
#define HELP_SCREEN_PATH "./res/help.txt"
#define OPTION_SCREEN_PATH "./res/option.txt"
#define GAMEBOX_1P_PATH "./res/gamebox_1P.txt"
#define GAMEBOX_2P_PATH "./res/gamebox_2P.txt"

class MENU
{
private:
	File file;
public:
	MENU()
	{
		file = File();
	}

	void Show_Main()
	{
		system("cls");
		file.File_Open(MAIN_SCREEN_PATH);
	}

	void Show_Option()
	{
		char key = ' ';

		system("cls");
		file.File_Open(OPTION_SCREEN_PATH);
		while (key != 'e')
			key = _getch();
	}

	void Show_Rank()
	{
		char key = ' ';

		system("cls");
		file.File_Open(RANKING_SCREEN_PATH);
		while (key != 'e')
			key = _getch();
	}

	void Show_Help()
	{
		char key = ' ';

		system("cls");
		file.File_Open(HELP_SCREEN_PATH);
		while (key != 'e')
			key = _getch();
	}

	void New_Game()
	{
		system("cls");

		Player player1 = Player(1);
		Game_Manager gm = Game_Manager();
		Play_Game(player1, gm);
	}

	void Load_Game()
	{
		//select 1p or 2p
		//input ID
		//Data Load
		//Play_Game_1P() or Play_Game_2P()
	}

	void Play_Game(Player& player, Game_Manager& gm)
	{
		double speed = gm.Cal_Speed();
		char key = ' ';

		system("cls");
		//File_Open(GAMEBOX_1P_PATH);

		while (gm.Game_Over())
		{
			int block_x = BLOCK_X, block_y = BLOCK_Y;
			gm.Rand_Next_Block();

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
						case 72: while (gm.Check_Next_Line(block_x, block_y)) gm.Change_Board(&block_x, &block_y, 80); break;
						case 80: if (gm.Check_Next_Line(block_x, block_y)) gm.Change_Board(&block_x, &block_y, key); break;
						case 75: if (gm.Check_Left_Side(block_x, block_y)) gm.Change_Board(&block_x, &block_y, key); break;
						case 77: if (gm.Check_Right_Side(block_x, block_y)) gm.Change_Board(&block_x, &block_y, key); break;
						case 32: gm.Change_Board(&block_x, &block_y, 32);
						}
					}
				}
				if (gm.Check_Next_Line(block_x, block_y))
				{
					gm.Change_Board(&block_x, &block_y, 80); // down
					Sleep(speed);
				}
				else
				{
					gm.Updata_Top();
					gm.Score_Check(&block_x, &block_y);
					break;
				}
			}
		}
		std::cout << "Game Over\n";
	}
};