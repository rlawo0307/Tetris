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
#define BOARD_POS_X 5
#define BOARD_POS_Y 5

#define BLOCK_COL 4
#define BLOCK_ROW 4
#define BLOCK_X 0
#define BLOCK_Y 0

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
		falling_speed = 1.0;
		i_next_block = 0;
		memset(board, 0, sizeof(board));
	}

	double falling_speed;
	int i_next_block; //index of next block
	int board[BOARD_COL][BOARD_ROW];
	int cur_block[BLOCK_COL][BLOCK_ROW];

	void Rand_Next_Block()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(1, 7);
		i_next_block = dis(gen);

		memset(cur_block, 0, sizeof(cur_block));

		switch (i_next_block)
		{
		case 1: cur_block[0][0] = cur_block[1][0] = cur_block[2][0] = cur_block[3][0] = i_next_block; break;
		case 2: cur_block[2][3] = cur_block[3][1] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		case 3: cur_block[2][1] = cur_block[3][1] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		case 4: cur_block[2][2] = cur_block[3][1] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		case 5: cur_block[2][2] = cur_block[2][3] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
		case 6: cur_block[2][2] = cur_block[2][3] = cur_block[3][1] = cur_block[3][2] = i_next_block; break;
		case 7: cur_block[2][1] = cur_block[2][2] = cur_block[3][2] = cur_block[3][3] = i_next_block; break;
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

	void Change_Board(int* cur_block_x, int* cur_block_y, char key)
	{
		//clear current falling block
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (cur_block[i][j] != 0)
					board[*cur_block_y + i][*cur_block_x + j] = 0;

		switch(key)
		{
		case 80: (*cur_block_y)++; break; //DOWN
		case 75: (*cur_block_x)--; break; // LEFT
		case 77: (*cur_block_x)++; break; // RIGHT
		//space 
		}
		
		//change next falling block
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (cur_block[i][j] != 0)
					board[*cur_block_y + i][*cur_block_x + j] = cur_block[i][j];
		
		Print_Board();
	}

	bool Check_Game_Over(int block_x, int block_y)
	{
		/*
		int block_start_row = -1, block_start_col = -1;

		//Find_Start_Index(&block_start_row, &block_start_col);
		if (block_start_row == 0)
			return true;
		*/
		return false;
	}

	bool Check_Next_Line(int block_x, int block_y)
	{
		//reach end of board
		if (block_y + BLOCK_COL == BOARD_COL)
			return false;

		//reach top of block
		for (int i = 0; i < BLOCK_ROW; i++)
			if (cur_block[BLOCK_COL - 1][i] != 0
				&& board[block_y + BLOCK_COL][block_x + i] != 0)
				return false;
		return true;
	}

	bool Check_Left_Side(int block_x, int block_y)
	{
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (cur_block[i][j] != 0)
				{
					if (block_x + j == 0 //reach end of board
						|| board[block_y + i][block_x + j - 1] != 0) // reach left of block
						return false;
					break;
				}
		return true;
	}

	bool Check_Right_Side(int block_x, int block_y)
	{
		for (int i = 0; i<BLOCK_COL; i++)
			for (int j = BLOCK_ROW - 1; j >= 0; j--)
				if (cur_block[i][j] != 0)
				{
					if (block_x + j ==  BOARD_ROW-1// reach end of board
						|| board[block_y + i][block_x + j + 1] != 0)
						return false;
					break;
				}
		return true;
	}

	void Print_Board()
	{
		for (int i = 0; i < BOARD_COL; i++)
		{
			if (i == 0 || i == BOARD_COL - 1)
				std::cout << "************************************\n";
			Cursor_Move(BOARD_POS_X, BOARD_POS_Y+i);
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


