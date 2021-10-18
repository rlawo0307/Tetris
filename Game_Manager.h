#pragma once

#include <iostream>
#include <random>
#include "Cursor.h"
#include "File.h"
#include "var.h"

#define SPEED_CHAGNE_PATH "./res/speed_change.txt"
#define GAMEBOX_PATH "./res/gamebox.txt"
#define SAVE_WAIT_PATH "./res/save_wait.txt"
#define GAME_MENU_PATH "./res/game_menu.txt"

#define GAMEBOX_X BOX_X
#define GAMEBOX_Y BOX_Y
#define BOARD_X GAMEBOX_X+2
#define BOARD_Y GAMEBOX_Y+2
#define SCORE_X GAMEBOX_X+BOARD_ROW+25
#define SCORE_Y GAMEBOX_Y+BOARD_COL-2
#define SPEED_X SCORE_X
#define SPEED_Y SCORE_Y+2
#define GAME_MENU_X GAMEBOX_X+45
#define GAME_MENU_Y GAMEBOX_Y

#define BLOCK_X 2
#define BLOCK_Y -3
#define NEXT_BLOCK_X BOARD_X+BOARD_ROW+16
#define NEXT_BLOCK_Y BOARD_Y+4

#define C_EMPTY 15 
#define C_BLOCK1 4 
#define C_BLOCK2 2 
#define C_BLOCK3 1 
#define C_BLOCK4 14 
#define C_BLOCK5 3
#define C_BLOCK6 6
#define C_BLOCK7 5

class Game_Manager
{
private:
	Cursor cs;
	File file;
	Player player;
	Data data;
	int color[8] = { C_EMPTY, C_BLOCK1, C_BLOCK2, C_BLOCK3, C_BLOCK4, C_BLOCK5,C_BLOCK6, C_BLOCK7 };
	int score;

public:

	void Init_GM(std::string& ID)
	{
		player.Set_ID(ID);
		player.Set_Score(0);
		score = player.Get_Score();
		data.falling_speed = 4.0;
		Init_Board();
		data.top = BOARD_COL - 1;
		data.block_x = BLOCK_X;
		data.block_y = BLOCK_Y;
	}

	void Set_Data(std::string ID, int score, DATA& ori_data)
	{
		player.Set_ID(ID);
		player.Set_Score(score);
		memcpy(&data, &ori_data, sizeof(Data));
		this->score = score;
	}

	void Get_Data(std::string& des_ID, int* score, Data& des_data)
	{
		des_ID = player.Get_ID();
		*score = player.Get_Score();
		memcpy(&des_data, &data, sizeof(Data));
	}

	void Init_Board()
	{
		for (int i = 0; i < BOARD_COL; i++)
			for (int j = 0; j < BOARD_ROW; j++)
				data.board[i][j] = 0;
	}

	void Init_Block(int (*block)[BLOCK_ROW])
	{
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				block[i][j] = 0;
	}

	void Rand_Next_Block(int op)
	{
		data.block_x = BLOCK_X;
		data.block_y = BLOCK_Y;
		Init_Block(data.cur_block);
		if (op == 0)
			Rand_Block(data.cur_block);
		else
		{
			for (int i = 0; i < BLOCK_COL; i++)
				for (int j = 0; j < BLOCK_ROW; j++)
					data.cur_block[i][j] = data.next_block[i][j];
		}
		Init_Block(data.next_block);
		Rand_Block(data.next_block);

		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (BLOCK_Y + i >= 0)
					data.board[BLOCK_Y + i][BLOCK_X + j] = data.cur_block[i][j];

		Print_Board();
	}

	void Rand_Block(int (*block)[BLOCK_ROW])
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(1, 7);
		int i = dis(gen);

		switch (i)
		{
		case 1: block[0][3] = block[1][3] = block[2][3] = block[3][3] = i; break;
		case 2: block[2][3] = block[3][1] = block[3][2] = block[3][3] = i; break;
		case 3: block[2][1] = block[3][1] = block[3][2] = block[3][3] = i; break;
		case 4: block[2][2] = block[3][1] = block[3][2] = block[3][3] = i; break;
		case 5: block[2][2] = block[2][3] = block[3][2] = block[3][3] = i; break;
		case 6: block[2][2] = block[2][3] = block[3][1] = block[3][2] = i; break;
		case 7: block[2][1] = block[2][2] = block[3][2] = block[3][3] = i; break;
		}
	}

	bool Check_Next_Line()
	{
		//reach bottom
		if (data.block_y + BLOCK_COL == BOARD_COL)
			return false;
		//reach other block
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (data.cur_block[i][j] != 0 && (i + 1 == BLOCK_COL || data.cur_block[i + 1][j] == 0))
					if(data.board[data.block_y + i + 1][data.block_x + j] != 0)
						return false;
		return true;
	}

	bool Check_Left_Side()
	{
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (data.cur_block[i][j] != 0)
				{
					if (data.block_x + j == 0 //reach end of board
						|| data.board[data.block_y + i][data.block_x + j - 1] != 0) // reach other block
						return false;
					break;
				}
		return true;
	}

	bool Check_Right_Side()
	{
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = BLOCK_ROW - 1; j >= 0; j--)
				if (data.cur_block[i][j] != 0)
				{
					if (data.block_x + j == BOARD_ROW - 1// reach end of board
						|| data.board[data.block_y + i][data.block_x + j + 1] != 0)
						return false;
					break;
				}
		return true;
	}

	void Change_Board(char key)
	{
		//clear prev block
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (data.cur_block[i][j] != 0)
					data.board[data.block_y + i][data.block_x + j] = 0;

		switch (key)
		{
		case 80: (data.block_y)++; break; //DOWN
		case 75: (data.block_x)--; break; // LEFT
		case 77: (data.block_x)++; break; // RIGHT
		case 32: Rotate_Block(); break; //SPACE 
		}

		//change next block
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (data.cur_block[i][j] != 0)
					data.board[data.block_y + i][data.block_x + j] = data.cur_block[i][j];

		Print_Board();
	}

	void Rotate_Block()
	{
		bool check = true;
		int c_cnt = 0, r_cnt = 0;
		int tmp[BLOCK_COL][BLOCK_ROW] = { 0, };

		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
				if (data.cur_block[i][j] != 0)
					tmp[j][BLOCK_ROW - 1 - i] = data.cur_block[i][j];

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
				if (tmp[i][j] != 0 && data.board[data.block_y + i][data.block_x + j] != 0)
				{
					check = false;
					break;
				}
		if (check)
		{
			for (int i = 0; i < BLOCK_COL; i++)
				for (int j = 0; j < BLOCK_ROW; j++)
					data.cur_block[i][j] = tmp[i][j];
		}
		else
			return;
	}

	void Updata_Top()
	{
		for (int i = 0; i < BOARD_COL; i++)
			for (int j = 0; j < BOARD_ROW; j++)
				if (data.board[i][j] != 0 && data.top > i)
				{
					data.top = i;
					return;
				}
	}

	void Score_Check()
	{
		bool check;

		for (int i = 0; i < BLOCK_COL; i++)
		{
			check = true;
			for (int j = 0; j < BOARD_ROW; j++)
				if (data.board[data.block_y + i][j] == 0)
				{
					check = false;
					break;
				}
			if (check)
			{
				score += BOARD_ROW;
				player.Set_Score(score);
				for (int k = data.block_y + i; k >= 0; k--)
					for (int j = 0; j < BOARD_ROW; j++)
						if (k == 0)
							data.board[k][j] = 0;
						else
							data.board[k][j] = data.board[k - 1][j];
			}
		}
	}

	void Print_Board()
	{
		file.Print_File(GAMEBOX_PATH, GAMEBOX_X, GAMEBOX_Y);
		for (int i = 0; i < BOARD_COL; i++)
		{
			cs.Cursor_Move(BOARD_X, BOARD_Y + i);
			for (int j = 0; j < BOARD_ROW; j++)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[data.board[i][j]]);
				std::cout << "бс";
			}
		}
		Print_Score();
		Print_Speed(data.falling_speed);
		for (int i = 0; i < BLOCK_COL; i++)
		{
			for (int j = 0; j < BLOCK_ROW; j++)
			{
				cs.Cursor_Move(NEXT_BLOCK_X+j*2, NEXT_BLOCK_Y + i);
				if (data.next_block[i][j] != 0)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[data.next_block[i][j]]);
					std::cout << "бс";
				}
			}
		}
	}

	void Print_Score()
	{
		cs.Cursor_Move(SCORE_X, SCORE_Y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[0]);
		std::cout << score << std::endl;
	}

	void Print_Speed(int speed)
	{
		cs.Cursor_Move(SPEED_X, SPEED_Y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[0]);
		std::cout << speed << " " << std::endl;
	}

	void Change_Speed(double* speed)
	{
		char key = ' ';
		int tmp = data.falling_speed;

		do
		{
			file.Print_File(SPEED_CHAGNE_PATH, GAME_MENU_X, GAME_MENU_Y);
			key = _getch();
			if (key == 13 || key == 27)
			{
				if (key == 13)
				{
					data.falling_speed = tmp;
					*speed = Cal_Speed();
				}
				file.Print_File(GAME_MENU_PATH, GAME_MENU_X, GAME_MENU_Y);
				Print_Speed(data.falling_speed);
				return;
			}
			else if (key == 72 || key == 80)
			{
				if (key == 72 && tmp < 10)
					tmp++;
				else if(key == 80 && tmp > 1)
					tmp--;
				Print_Speed(tmp);
			}
		} while (1);
	}

	double Cal_Speed()
	{
		return 1000 * (1 / data.falling_speed);
	}

	bool Game_Over()
	{
		return data.top <= 0 ? true : false;
	}

};

