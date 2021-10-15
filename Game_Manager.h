#pragma once

#include <iostream>
#include <random>
#include "Cursor.h"

#define C_EMPTY 15 //white
#define C_BLOCK1 1 //blue
#define C_BLOCK2 2 //green
#define C_BLOCK3 3 //cyan
#define C_BLOCK4 4 //red
#define C_BLOCK5 5 //magenta
#define C_BLOCK6 6 //brown
#define C_BLOCK7 14 // yellow

#define BOARD_COL 20
#define BOARD_ROW 10
#define BOARD_X 5
#define BOARD_Y 5

#define BLOCK_COL 4
#define BLOCK_ROW 4
#define BLOCK_X 2
#define BLOCK_Y -3

#define SCORE_X BOARD_X+BOARD_ROW+2
#define SCORE_Y BOARD_Y+BOARD_COL+2

#define SPEED_X SCORE_X
#define SPEED_Y SCORE_Y+1

class Game_Manager
{
private:
	double falling_speed;
	int i_next_block; //index of next block
	int board[BOARD_COL][BOARD_ROW];
	int cur_block[BLOCK_COL][BLOCK_ROW];
	int top = BOARD_COL - 1;
	int color[8] = { C_EMPTY, C_BLOCK1, C_BLOCK2, C_BLOCK3, C_BLOCK4, C_BLOCK5,C_BLOCK6, C_BLOCK7 };
	Cursor cs;

public:
	int score;

	Game_Manager()
	{
		cs = Cursor();
		score = 0;
		falling_speed = 4.0;
		i_next_block = 0;
		Init_Board();
	}

	double Cal_Speed()
	{
		return 1000 * (1 / falling_speed);
	}

	void Init_Board()
	{
		for (int i = 0; i < BOARD_COL; i++)
			for (int j = 0; j < BOARD_ROW; j++)
				board[i][j] = 0;

		//Print_Board();
	}

	void Init_Cur_Block()
	{
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				cur_block[i][j] = 0;
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
			if (cur_block[BLOCK_COL - 1][i] != 0 && board[block_y + BLOCK_COL][block_x + i] != 0)
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
						|| board[block_y + i][block_x + j - 1] != 0) // reach other block
						return false;
					break;
				}
		return true;
	}

	bool Check_Right_Side(int block_x, int block_y)
	{
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = BLOCK_ROW - 1; j >= 0; j--)
				if (cur_block[i][j] != 0)
				{
					if (block_x + j == BOARD_ROW - 1// reach end of board
						|| board[block_y + i][block_x + j + 1] != 0)
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
				if (cur_block[i][j] != 0)
					board[prev_block_y + i][prev_block_x + j] = 0;

		switch (key)
		{
		case 80: next_block_y++; break; //DOWN
		case 75: next_block_x--; break; // LEFT
		case 77: next_block_x++; break; // RIGHT
		case 32: Rotate_Block(*cur_block_x, *cur_block_y); break; //SPACE 
		}

		//change next block
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (cur_block[i][j] != 0)
					board[next_block_y + i][next_block_x + j] = cur_block[i][j];

		*cur_block_x = next_block_x;
		*cur_block_y = next_block_y;
		Print_Board();
	}

	void Rotate_Block(int block_x, int block_y)
	{
		bool check = true;
		int c_cnt = 0, r_cnt = 0;
		int tmp[BLOCK_COL][BLOCK_ROW] = { 0, };

		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (cur_block[i][j] != 0)
					tmp[j][BLOCK_ROW - 1 - i] = cur_block[i][j];

		while (check)
		{
			for (int i = 0; i < BLOCK_ROW; i++)
				if (tmp[BLOCK_COL - c_cnt - 1][i] != 0)
				{
					check = false;
					break;
				}
			if (check)
				c_cnt++;
		}
		check = true;
		while (check)
		{
			for (int i = 0; i < BLOCK_COL; i++)
				if (tmp[i][BLOCK_ROW - r_cnt - 1] != 0)
				{
					check = false;
					break;
				}
			if (check)
				r_cnt++;
		}

		for (int i = BLOCK_COL - c_cnt - 1; i >= 0; i--)
			for (int j = BLOCK_ROW - r_cnt - 1; j >= 0; j--)
				if (tmp[i][j] != 0)
				{
					tmp[i + c_cnt][j + r_cnt] = tmp[i][j];
					if (c_cnt != 0 || r_cnt != 0)
						tmp[i][j] = 0;
				}

		check = true;
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (tmp[i][j] != 0 && board[block_y + i][block_x + j] != 0)
				{
					check = false;
					break;
				}
		if (check)
		{
			Init_Cur_Block();

			for (int i = 0; i < BLOCK_COL; i++)
				for (int j = 0; j < BLOCK_ROW; j++)
					cur_block[i][j] = tmp[i][j];
		}
		else
			return;
	}

	void Print_Board()
	{
		for (int i = 0; i < BOARD_COL; i++)
		{
			cs.Cursor_Move(BOARD_X, BOARD_Y + i);
			for (int j = 0; j < BOARD_ROW; j++)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[board[i][j]]);
				std::cout << "��";
			}
		}
		Print_Score();
		Print_Speed();
	}

	void Updata_Top()
	{
		for (int i = 0; i < BOARD_COL; i++)
			for (int j = 0; j < BOARD_ROW; j++)
				if (board[i][j] != 0 && top > i)
				{
					top = i;
					return;
				}
	}

	void Score_Check(int* block_x, int* block_y)
	{
		bool check;

		for (int i = 0; i < BLOCK_COL; i++)
		{
			check = true;
			for (int j = 0; j < BOARD_ROW; j++)
				if (board[*block_y + i][j] == 0)
				{
					check = false;
					break;
				}
			if (check)
			{
				score += BOARD_ROW;
				for (int k = *block_y + i; k >= 0; k--)
					for (int j = 0; j < BOARD_ROW; j++)
						if (k == 0)
							board[k][j] = 0;
						else
							board[k][j] = board[k - 1][j];
			}
		}
	}

	bool Game_Over()
	{
		return top > 0 ? true : false;
	}

	void Print_Score()
	{
		cs.Cursor_Move(SCORE_X, SCORE_Y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[0]);
		std::cout << "\n* Score : " << score << std::endl;
	}

	void Print_Speed()
	{
		cs.Cursor_Move(SPEED_X, SPEED_Y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[0]);
		std::cout << "\n* Speed : " << falling_speed << std::endl;
	}

	void Change_Speed(double* speed)
	{
		char key = ' ';
		int tmp = falling_speed;

		do
		{
			key = _getch();
			cs.Cursor_Move(50, 10);
			std::cout << "Speed Up(��), Speed Down(��)\n";
			switch (key)
			{
			case 72: tmp++; break; //UP
			case 80: tmp--; break; //DOWN
			case 27: break;//esc
			case 13: falling_speed = tmp; *speed = Cal_Speed(); break; //enter
			}
			cs.Cursor_Move(SPEED_X, SPEED_Y);
			std::cout << "\n* Speed : " << tmp << std::endl;
		} while (key != 27 && key != 13);
	}
};

