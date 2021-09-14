#pragma once

#define MAIN_SCREEN_PATH "./res/main_menu.txt"
#define RANKING_SCREEN_PATH "./res/rank.txt"
#define HELP_SCREEN_PATH "./res/help.txt"
#define OPTION_SCREEN_PATH "./res/option.txt"
#define GAMEBOX_1P_PATH "./res/gamebox_1P.txt"
#define GAMEBOX_2P_PATH "./res/gamebox_2P.txt"

#define BOARD_COL 10
#define BOARD_ROW 20
//Func.cpp
class Cursor
{
public:
	int x;
	int y;
	
	void Get_Cursor();
	void Set_Cursor();
};

class Game_Setting
{
public:
	double falling_speed;
	int i_next_block; //index of next block
	int c_next_block; // color of next block
	int board[BOARD_COL][BOARD_ROW] = { 0, };
};

class Player
{
public:
	std::string ID;
	int score;
	Game_Setting data;
};


