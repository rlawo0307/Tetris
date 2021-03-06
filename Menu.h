#pragma once

#include <iostream>
#include "File.h"
#include "Player.h"
#include "Game_Manager.h"
#include "Cursor.h"
#include "var.h"

#define MAIN_SCREEN_PATH "./res/main_menu.txt"
#define HELP_PATH "./res/help.txt"
#define OPTION_PATH "./res/option.txt"
#define GAME_MENU_PATH "./res/game_menu.txt"
#define SAVE_COMPLETE_PATH "./res/save_complete.txt"
#define GAME_OVER_PATH "./res/game_over.txt"
#define SAVE_PAUSE_PATH "./res/save_pause.txt"
#define ASK_SAVE_PATH "./res/ask_save.txt"
#define RANK_PATH "./rank/rank.txt"

#define MAIN_SCREEN_X BOX_X
#define MAIN_SCREEN_Y BOX_Y
#define HELP_X MAIN_SCREEN_X+25
#define HELP_Y MAIN_SCREEN_Y
#define OPTION_X HELP_X
#define OPTION_Y HELP_Y
#define GAME_OVER_X MAIN_SCREEN_X+23
#define GAME_OVER_Y MAIN_SCREEN_Y
#define SAVE_PAUSE_X MAIN_SCREEN_X+6
#define SAVE_PAUSE_Y MAIN_SCREEN_Y+10
#define GAME_MENU_X MAIN_SCREEN_X+45
#define GAME_MENU_Y MAIN_SCREEN_Y
#define ASK_SAVE_X GAME_MENU_X
#define ASK_SAVE_Y GAME_MENU_Y
#define RANK_X HELP_X
#define RANK_Y HELP_Y


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

	void Game(int op)
	{
		char key = ' ';
		Game_Manager gm = Game_Manager();
		std::string ID;

		if (op == 0) // new game
		{
			file.Print_File(INPUT_ID_PATH, ID_X, ID_Y);
			cs.Cursor_Move(ID_X + 10, ID_Y + 2);
			std::cin >> ID;
			gm.Init_GM(ID);
		}
		else // load_game
		{
			int score;
			Data data;

			do
			{
				file.Print_File(INPUT_ID_PATH, ID_X, ID_Y);
				cs.Cursor_Move(ID_X + 10, ID_Y + 2);
				std::cin >> ID;
			} while (!file.Read_File(ID, &score, data));
			gm.Set_Data(ID, score, data);
		}
		do
		{
			if(key == 'r')
				gm.Init_GM(ID);
			system("cls");
			Play_Game(gm, op);
			if (!gm.Game_Over())
				return;
			file.Print_File(GAME_OVER_PATH, GAME_OVER_X, GAME_OVER_Y);
			key = _getch();
		} while (key == 'r' || key != 'h');

		while (key != 'h')
			key = _getch();
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

		file.Print_File(SAVE_PAUSE_PATH, SAVE_PAUSE_X, SAVE_PAUSE_Y);
		do
		{
			file.Print_File(GAME_MENU_PATH, GAME_MENU_X, GAME_MENU_Y);
			key = _getch();
			switch (key)
			{
			case 'c': gm.Change_Speed(speed); break;
			case 'h': key = Save(gm, key); if (key != 27) return key; else break;
			case 's': return Save(gm, key);
			case 27: file.Clear_File(GAME_MENU_PATH, GAME_MENU_X, GAME_MENU_Y); return key; //esc
			}
		} while (1);
	}

	void Play_Game(Game_Manager& gm, int op)
	{
		double speed = gm.Cal_Speed();
		char key = ' ';

		if(op == 0) // new game
			gm.Rand_Next_Block(0);
		while (1)
		{
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
						case 72: while (gm.Check_Next_Line()) gm.Change_Board(80); break;
						case 80: if (gm.Check_Next_Line()) gm.Change_Board(key); break;
						case 75: if (gm.Check_Left_Side()) gm.Change_Board(key); break;
						case 77: if (gm.Check_Right_Side()) gm.Change_Board(key); break;
						case 32: gm.Change_Board(32); break;
						case 27: if (Show_Game_Menu(gm, &speed) == 'h') return ; else gm.Print_Board(); break; //esc
						}
					}
				}
				if (gm.Check_Next_Line())
				{
					gm.Change_Board(80); // down
					Sleep(speed);
				}
				else
				{
					gm.Updata_Top();
					gm.Score_Check();
					break;
				}
			} while (1);
			if (gm.Game_Over())
				break;
			gm.Rand_Next_Block(1);
		}
	}

	char Save(Game_Manager& gm, char op)
	{
		char key = ' ';
		std::string ID;
		int score;
		Data data;

		if (op == 'h') // go home
		{
			file.Print_File(ASK_SAVE_PATH, ASK_SAVE_X, ASK_SAVE_Y);
			while (key != 'y' && key != 'n' && key != 27)
				key = _getch();
			if (key == 'n')
				return op;
			else if (key == 27)
			{
				file.Clear_File(ASK_SAVE_PATH, ASK_SAVE_X, ASK_SAVE_Y);
				return key;
			}
		}
		file.Print_File(SAVE_WAIT_PATH, GAME_MENU_X, GAME_MENU_Y);
		Sleep(1000);

		gm.Get_Data(ID, &score, data);
		file.Write_File(ID, score, data);
		file.Print_File(SAVE_COMPLETE_PATH, GAME_MENU_X, GAME_MENU_Y);
		
		if (op == 's')
		{
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
		else
		{
			cs.Cursor_Move(GAME_MENU_X+1, GAME_MENU_Y+5);
			std::cout << "                        ";
			cs.Cursor_Move(GAME_MENU_X+1, GAME_MENU_Y + 7);
			std::cout << "                        ";
			Sleep(1000);
			return op;
		}
		
	}
};