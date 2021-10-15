#pragma once

#include <iostream>
#include "File.h"
#include "Player.h"
#include "Game_Manager.h"
#include "Cursor.h"

#define MAIN_SCREEN_PATH "./res/main_menu.txt"
#define RANKING_SCREEN_PATH "./res/rank.txt"
#define HELP_SCREEN_PATH "./res/help.txt"
#define OPTION_SCREEN_PATH "./res/option.txt"
#define GAMEBOX_1P_PATH "./res/gamebox.txt"
#define NEW_GAME_PATH "./res/new_game.txt"
#define GAME_MENU "./res/game_menu.txt"

#define GAME_MENU_X 30
#define GAME_MENU_Y 10

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
		file.Print_File(MAIN_SCREEN_PATH, 0, 0);
	}

	void Show_Option()
	{
		char key = ' ';

		system("cls");
		//file.File_Open(OPTION_SCREEN_PATH);
		while (key != 'e')
			key = _getch();
	}

	void Show_Rank()
	{
		char key = ' ';

		system("cls");
		//file.File_Open(RANKING_SCREEN_PATH);
		while (key != 'e')
			key = _getch();
	}

	void Show_Help()
	{
		char key = ' ';

		system("cls");
		//file.File_Open(HELP_SCREEN_PATH);
		while (key != 'e')
			key = _getch();
	}

	void New_Game()
	{
		system("cls");
		//file.File_Open(NEW_GAME_PATH);

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

	void Show_Game_Menu(Game_Manager& gm, double* speed)
	{
		char key = ' ';

		file.Print_File(GAME_MENU, GAME_MENU_X, GAME_MENU_Y);
		do
		{
			key = _getch();
			switch (key)
			{
			case 'c': gm.Change_Speed(speed); break;
			case 'h': break;
			case 's': break;
			case 27: file.Clear_File(GAME_MENU, GAME_MENU_X, GAME_MENU_Y); return; //esc
			}
		} while (1);
	}

	void Play_Game(Player& player, Game_Manager& gm)
	{
		double speed = gm.Cal_Speed();
		char key = ' ';

		system("cls");
		file.Print_File(GAMEBOX_1P_PATH, 0, 0);

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
						case 27: Show_Game_Menu(gm, &speed); gm.Print_Board(); break; //esc
						default: std::cout << (int)key << std::endl;
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