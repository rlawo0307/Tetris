#pragma once

#define MAIN_SCREEN_PATH "./res/main_menu.txt"
#define RANKING_SCREEN_PATH "./res/"
#define HELP_SCREEN_PATH "./res/"
#define OPTION_SCREEN_PATH "./res"
#define GAME_BOX_PATH "./res"

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
	int falling_speed;
	int i_next_block; //index of next block
	int c_next_block; // color of next block
	int board[10][20] = { 0, };
};

class Player
{
public:
	std::string ID;
	int score;
	Game_Setting* data = nullptr;
};

class Game
{
public:
	void Play_Game_1P();
	void Play_Game_2P();
};

