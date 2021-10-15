#pragma once

#include <iostream>
#include "File.h"
#include "Player.h"
#include "Game_Manager.h"
#include "Cursor.h"

#define MAIN_SCREEN_PATH "./res/main_menu.txt"
#define RANK_PATH "./res/rank.txt"
#define HELP_PATH "./res/help.txt"
#define OPTION_PATH "./res/option.txt"
#define GAME_MENU_PATH "./res/game_menu.txt"

#define MAIN_SCREEN_X 10
#define MAIN_SCREEN_Y 10
#define HELP_X MAIN_SCREEN_X+10
#define HELP_Y MAIN_SCREEN_Y+3
#define RANK_X MAIN_SCREEN_X+25
#define RANK_Y MAIN_SCREEN_Y
#define OPTION_X HELP_X
#define OPTION_Y HELP_Y
#define GAME_MENU_X MAIN_SCREEN_X+8
#define GAME_MENU_Y MAIN_SCREEN_Y+5

class MENU
{
private:
	File file;
	Cursor cs;

public:
	MENU()
	{
		file = File();
		cs = Cursor();
	}

	void Show_Main()
	{
		system("cls");
		file.Print_File(MAIN_SCREEN_PATH, MAIN_SCREEN_X, MAIN_SCREEN_Y);
	}

	void New_Game()
	{
		Player player1 = Player(1);
		Game_Manager gm = Game_Manager();
		system("cls");
		Play_Game(player1, gm);
	}

	void Load_Game()
	{
		//select 1p or 2p
		//input ID
		//Data Load
		//Play_Game_1P() or Play_Game_2P()
	}

	void Show_Help()
	{
		char key = ' ';

		file.Print_File(HELP_PATH, HELP_X, HELP_Y);
		while (key != 27) // esc
			key = _getch();
	}

	void Show_Rank()
	{
		char key = ' ';

		file.Print_File(RANK_PATH, RANK_X, RANK_Y);
		while (key != 27) // esc
			key = _getch();
	}

	void Show_Option()
	{
		char key = ' ';

		file.Print_File(OPTION_PATH, OPTION_X, OPTION_Y);
		while (key != 27) // esc
			key = _getch();
	}

	void Show_Game_Menu(Game_Manager& gm, double* speed)
	{
		char key = ' ';

		file.Print_File(GAME_MENU_PATH, GAME_MENU_X, GAME_MENU_Y);
		do
		{
			key = _getch();
			switch (key)
			{
			case 'c': gm.Change_Speed(speed); break;
			case 'h': break;
			case 's': break;
			case 27: file.Clear_File(GAME_MENU_PATH, GAME_MENU_X, GAME_MENU_Y); return; //esc
			}
		} while (1);
	}

	void Play_Game(Player& player, Game_Manager& gm)
	{
		double speed = gm.Cal_Speed();
		char key = ' ';

		while (gm.Game_Over())
		{
			int block_x = BLOCK_X, block_y = BLOCK_Y;
			gm.Rand_Next_Block();
			do
			{
				gm.Print_Board();
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
						case 32: gm.Change_Board(&block_x, &block_y, 32); break;
						case 27: Show_Game_Menu(gm, &speed); gm.Print_Board(); break; //esc
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
			} while (1);
		}
		std::cout << "Game Over\n";
	}
};