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

#define BOARD_COL 5
#define BOARD_ROW 5
#define BOARD_X 5
#define BOARD_Y 5

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
	int color[8] = { NULL, FOREGROUND_RED, FOREGROUND_BLUE, FOREGROUND_GREEN,
		FOREGROUND_RED | FOREGROUND_BLUE , FOREGROUND_RED | FOREGROUND_GREEN,
	FOREGROUND_BLUE | FOREGROUND_GREEN, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN };
public:
	Game()
	{
		falling_speed = 1.0;
		i_next_block = c_next_block = Rand_Next_Block();
		for (int i = 0; i < BOARD_COL; i++)
			for (int j = 0; j < BOARD_ROW; j++)
				board[i][j] = 0;
	}

	double falling_speed;
	int i_next_block; //index of next block
	int c_next_block; // color of next block
	int board[BOARD_COL][BOARD_ROW];

	int Rand_Next_Block()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(1, 7);
		return dis(gen);
	}

	void Print_Board()
	{
		for (int i = 0; i < BOARD_COL; i++)
		{
			Cursor_Move(BOARD_X, BOARD_Y+i);
			for (int j = 0; j < BOARD_ROW; j++)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[board[i][j]]);
				std::cout << "��";
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


