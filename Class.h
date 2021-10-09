#pragma once
#include <iostream>
#include <random>
#include <string>
#include "Windows.h"
#include "Func.h"
#include <conio.h> // _kbhit(),_getch(0

#define MAIN_SCREEN_PATH "./res/main_menu.txt"
#define RANKING_SCREEN_PATH "./res/rank.txt"
#define HELP_SCREEN_PATH "./res/help.txt"
#define OPTION_SCREEN_PATH "./res/option.txt"
#define GAMEBOX_1P_PATH "./res/gamebox_1P.txt"
#define GAMEBOX_2P_PATH "./res/gamebox_2P.txt"

#define C_EMPTY 15 //white
#define C_BLOCK1 1 //blue
#define C_BLOCK2 2 //green
#define C_BLOCK3 3 //cyan
#define C_BLOCK4 4 //red
#define C_BLOCK5 5 //magenta
#define C_BLOCK6 6 //brown
#define C_BLOCK7 7 // darkgray

#define BOARD_COL 20
#define BOARD_ROW 10
#define BOARD_POS_X 5
#define BOARD_POS_Y 5

#define BLOCK_COL 4
#define BLOCK_ROW 4
#define BLOCK_X 2
#define BLOCK_Y -3

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
public:
	Game()
	{
		falling_speed = 4.0;
		i_next_block = 0;
		memset(board, 0, sizeof(board));
	}

	double falling_speed;
	int i_next_block; //index of next block
	int board[BOARD_COL][BOARD_ROW];
	int cur_block[BLOCK_COL][BLOCK_ROW];
	int top = BOARD_COL-1;

	void Init_Board()
	{
		for (int i = 0; i < BOARD_COL; i++)
			for (int j = 0; j < BOARD_ROW; j++)
				board[i][j] = C_EMPTY;

		Print_Board();
	}

	void Init_Cur_Block()
	{
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				cur_block[i][j] = C_EMPTY;
	}

	void Rand_Next_Block()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(1, 7);
		i_next_block = dis(gen);

		Init_Cur_Block();

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

		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (BLOCK_Y + i >= 0)
						board[BLOCK_Y + i][BLOCK_X + j] = cur_block[i][j];
		
		Print_Board();
	}

	bool Check_Next_Line(int block_x, int block_y)
	{
		//reach bottom
		if (block_y + BLOCK_COL == BOARD_COL)
			return false;
		//reach other block
		for (int i = 0; i < BLOCK_ROW; i++)
			if (cur_block[BLOCK_COL - 1][i] != C_EMPTY && board[block_y + BLOCK_COL][block_x + i] != C_EMPTY)
				return false;
		return true;
	}

	bool Check_Left_Side(int block_x, int block_y)
	{
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (cur_block[i][j] != C_EMPTY)
				{
					if (block_x + j == 0 //reach end of board
						|| board[block_y + i][block_x + j - 1] != C_EMPTY) // reach other block
						return false;
					break;
				}
		return true;
	}

	bool Check_Right_Side(int block_x, int block_y)
	{
		for (int i = 0; i<BLOCK_COL; i++)
			for (int j = BLOCK_ROW - 1; j >= 0; j--)
				if (cur_block[i][j] != C_EMPTY)
				{
					if (block_x + j ==  BOARD_ROW-1// reach end of board
						|| board[block_y + i][block_x + j + 1] != C_EMPTY)
						return false;
					break;
				}
		return true;
	}

	void Change_Board(int* cur_block_x, int* cur_block_y, char key)
	{
		int prev_block_x = *cur_block_x, prev_block_y = *cur_block_y;
		int next_block_x = *cur_block_x, next_block_y = *cur_block_y;

		//clear prev block
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (cur_block[i][j] != C_EMPTY)
					board[prev_block_y + i][prev_block_x + j] = C_EMPTY;

		switch (key)
		{
		case 72: 
		case 80: next_block_y++; break; //DOWN
		case 75: next_block_x--; break; // LEFT
		case 77: next_block_x++; break; // RIGHT
		//space 
		}

		//change next block
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (cur_block[i][j] != C_EMPTY)
					board[next_block_y + i][next_block_x + j] = cur_block[i][j];

		*cur_block_x = next_block_x;
		*cur_block_y = next_block_y;
		Print_Board();
	}

	void Print_Board()
	{
		for (int i = 0; i < BOARD_COL; i++)
		{
			Cursor_Move(BOARD_POS_X, BOARD_POS_Y+i);
			for (int j = 0; j < BOARD_ROW; j++)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), board[i][j]);
				std::cout << "бс";
			}
		}
	}

	void Updata_Top()
	{
		for (int i = 0; i < BOARD_COL; i++)
			for (int j = 0; j < BOARD_ROW; j++)
				if (board[i][j] != C_EMPTY && top > i)
				{
					top = i;
					return;
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


