#pragma once
#include <iostream>
#include <random>
#include <string>
#include "Windows.h"
#include "Func.h"

#define MAIN_SCREEN_PATH "./res/main_menu.txt"
#define RANKING_SCREEN_PATH "./res/rank.txt"
#define HELP_SCREEN_PATH "./res/help.txt"
#define OPTION_SCREEN_PATH "./res/option.txt"
#define GAMEBOX_1P_PATH "./res/gamebox_1P.txt"
#define GAMEBOX_2P_PATH "./res/gamebox_2P.txt"

#define C_EMPTY FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define C_BLOCK1 FOREGROUND_RED
#define C_BLOCK2 FOREGROUND_GREEN
#define C_BLOCK3 FOREGROUND_BLUE
#define C_BLOCK4 FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
#define C_BLOCK5 FOREGROUND_BLUE | FOREGROUND_GREEN
#define C_BLOCK6 FOREGROUND_INTENSITY
#define C_BLOCK7 FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY

#define BOARD_COL 20
#define BOARD_ROW 10
#define BOARD_X 5
#define BOARD_Y 5

#define CUR_BLOCK_COL 2
#define CUR_BLOCK_ROW 3
#define CUR_BLOCK_X 2
#define CUR_BLOCK_Y 0

//Func.cpp
class Cursor
{
public:
	int x;
	int y;
	
	void Get_Cursor();
	void Set_Cursor();
};

class Game
{
private:
	int color[8] = { C_EMPTY , C_BLOCK1, C_BLOCK2, C_BLOCK3, C_BLOCK4, C_BLOCK5, C_BLOCK6 ,C_BLOCK7 };
public:
	Game()
	{
		falling_speed = 0.3;
		i_next_block = 0;
		memset(board, 0, sizeof(board));
		/*
		for (int i = 0; i < BOARD_COL; i++)
			for (int j = 0; j < BOARD_ROW; j++)
				board[i][j] = 0;
		*/
	}

	double falling_speed;
	int i_next_block; //index of next block
	int board[BOARD_COL][BOARD_ROW];
	int cur_block[CUR_BLOCK_COL][CUR_BLOCK_ROW];

	void Rand_Next_Block()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(1, 7);
		i_next_block = dis(gen);

		memset(cur_block, 0, sizeof(cur_block));

		switch (i_next_block)
		{
		case 1: cur_block[0][0] = cur_block[1][0] = i_next_block; break;
		case 2: cur_block[0][2] = cur_block[1][0] = cur_block[1][1] = cur_block[1][2] = i_next_block; break;
		case 3: cur_block[0][0] = cur_block[1][0] = cur_block[1][1] = cur_block[1][2] = i_next_block; break;
		case 4: cur_block[0][1] = cur_block[1][0] = cur_block[1][1] = cur_block[1][2] = i_next_block; break;
		case 5: cur_block[0][1] = cur_block[0][2] = cur_block[1][1] = cur_block[1][2] = i_next_block; break;
		case 6: cur_block[0][1] = cur_block[0][2] = cur_block[1][0] = cur_block[1][1] = i_next_block; break;
		case 7: cur_block[0][0] = cur_block[0][1] = cur_block[1][1] = cur_block[1][2] = i_next_block; break;
		/*
		case 1: cur_block[0][0] = cur_block[1][0] = cur_block[2][0] = cur_block[3][0] = i_next_block; break;
		case 2: cur_block[2][3] = cur_block[3][1] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		case 3: cur_block[2][1] = cur_block[3][1] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		case 4: cur_block[2][2] = cur_block[3][1] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		case 5: cur_block[2][2] = cur_block[2][3] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		case 6: cur_block[2][2] = cur_block[2][3] = cur_block[3][1] = cur_block[3][2] = i_next_block; break;
		case 7: cur_block[2][1] = cur_block[2][2] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		*/
		}
	}

	void Change_Board(int cur_x, int cur_y, char key)
	{
		int prev_x = cur_x, prev_y = cur_y;

		if (key == 80) // DOWN
		{
			prev_y
		}
		else if (key == 75) // LEFT
		{
			prev
		}
		else if (key == 77) // RIGHT
		{

		}
		//space 

		//clear last falling block
		for (int i = 0; i < CUR_BLOCK_COL; i++)
			for (int j = 0; j < CUR_BLOCK_ROW; j++)
				if(cur_block[i][j] != 0)
					board[CUR_BLOCK_Y + cur_y + i-1][CUR_BLOCK_X + j] = 0;

		//print current falling block
		for (int i = 0; i < CUR_BLOCK_COL; i++)
			for (int j = 0; j < CUR_BLOCK_ROW; j++)
				if (cur_block[i][j] != 0)
					board[CUR_BLOCK_Y + cur_y + i][CUR_BLOCK_X + j] = cur_block[i][j];
	}

	bool Check_Next_Line(int cur_y)
	{
		for (int i = 0; i < CUR_BLOCK_ROW; i++)
			if (cur_block[CUR_BLOCK_COL - 1][i] != 0 && board[CUR_BLOCK_Y + cur_y + CUR_BLOCK_COL - 1][CUR_BLOCK_X + i] != 0)
				return false;
		return true;
	}

	void Print_Board()
	{
		for (int i = 0; i < BOARD_COL; i++)
		{
			if (i == 0 || i == BOARD_COL - 1)
				std::cout << "************************************\n";
			Cursor_Move(BOARD_X, BOARD_Y+i);
			for (int j = 0; j < BOARD_ROW; j++)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[board[i][j]]);
				std::cout << "бс";
			}
		}
	}

	
};

class Player
{
public:
	Player()
	{
		this->ID = Input_ID();
		score = 0;
		data = Game();
	}

	std::string ID;
	int score;
	Game data;

	const std::string Input_ID()
	{
		std::string str;
		std::cout << "Player ID : ";
		std::cin >> str;
		return str;
	}
};


