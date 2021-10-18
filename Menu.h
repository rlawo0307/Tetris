#pragma once

#include <iostream>
#include "File.h"
#include "Player.h"
#include "Game_Manager.h"
#include "Cursor.h"
#include "var.h"

#define MAIN_SCREEN_PATH "./res/main_menu.txt"
#define RANK_PATH "./res/rank.txt"
#define HELP_PATH "./res/help.txt"
#define OPTION_PATH "./res/option.txt"
#define GAME_MENU_PATH "./res/game_menu.txt"
#define SAVE_COMPLETE_PATH "./res/save_complete.txt"
#define GAME_OVER_PATH "./res/game_over.txt"

#define MAIN_SCREEN_X BOX_X
#define MAIN_SCREEN_Y BOX_Y
#define RANK_X MAIN_SCREEN_X+25
#define RANK_Y MAIN_SCREEN_Y
#define HELP_X RANK_X
#define HELP_Y RANK_Y
#define OPTION_X RANK_X
#define OPTION_Y RANK_Y
#define GAME_OVER_X MAIN_SCREEN_X+23
#define GAME_OVER_Y MAIN_SCREEN_Y

#define GAME_MENU_X MAIN_SCREEN_X+45
#define GAME_MENU_Y MAIN_SCREEN_Y

class MENU
{
private:
	File file;
	Cursor cs;

public:

	void Show_Main()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		system("cls");
		file.Print_File(MAIN_SCREEN_PATH, MAIN_SCREEN_X, MAIN_SCREEN_Y);
	}

	void New_Game()
	{
		char key = ' ';

		Game_Manager gm = Game_Manager();
		do
		{
			if(key == 'r')
				gm.Init_GM();
			system("cls");
			Play_Game(gm);
			file.Print_File(GAME_OVER_PATH, GAME_OVER_X, GAME_OVER_Y);
			key = _getch();
		} while (key == 'r' && key != 'h');

		while (key != 'h')
			key = _getch();
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

	char Show_Game_Menu(Game_Manager& gm, double* speed)
	{
		char key = ' ';

		file.Print_File(GAME_MENU_PATH, GAME_MENU_X, GAME_MENU_Y);
		do
		{
			key = _getch();
			switch (key)
			{
			case 'c': gm.Change_Speed(speed); break;
			case 'h': return key;
			case 's': return Save(gm);
			case 27: file.Clear_File(GAME_MENU_PATH, GAME_MENU_X, GAME_MENU_Y); return key; //esc
			}
		} while (1);
	}

	void Play_Game(Game_Manager& gm)
	{
		double speed = gm.Cal_Speed();
		char key = ' ';
		char tmp = ' ';

		gm.Rand_Next_Block(0);
		while (1)
		{
			int block_x = BLOCK_X, block_y = BLOCK_Y;
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
						case 27: if (Show_Game_Menu(gm, &speed) == 'h') return; else gm.Print_Board(); break; //esc
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
			if (gm.Game_Over())
				break;
			gm.Rand_Next_Block(1);
		}
	}

	char Save(Game_Manager& gm)
	{
		char key = ' ';
		std::string ID;
		int score;
		Data data;

		file.Print_File(SAVE_WAIT_PATH, GAME_MENU_X, GAME_MENU_Y);
		Sleep(2000);

		gm.Get_Data(ID, &score, data);
		file.Write_File(ID, score, data);
		file.Print_File(SAVE_COMPLETE_PATH, GAME_MENU_X, GAME_MENU_Y);
		
		while (1)
		{
			key = _getch();
			if (key == 'h' || key == 27)
			{
				file.Clear_File(SAVE_COMPLETE_PATH, GAME_MENU_X, GAME_MENU_Y);
				break;
			}
		}
		return key;
	}
};