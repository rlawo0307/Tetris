#pragma once

#define MAIN_SCREEN_PATH "./res/"
#define RANKING_SCREEN_PATH "./res/"
#define HELP_SCREEN_PATH "./res/"
#define OPTION_SCREEN_PATH "./res"
#define GAME_BOX_PATH "./res"

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

class Command
{
public:
	void Show_Option();
	void Show_Rank();
	void Show_Help();
	void New_Game();
	void Load_Game();
};

class Game
{
public:
	void Play_Game_1P();
	void Play_Game_2P();
};


