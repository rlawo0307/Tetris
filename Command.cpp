#include <iostream>
#include <string>
#include "Command.h"
#include "Class.h"
#include "Func.h"
#include "Game.h"

void Show_Option()
{
	system("cls");
	File_Open(OPTION_SCREEN_PATH);
}

void Show_Rank()
{
	system("cls");
	File_Open(RANKING_SCREEN_PATH);
}

void Show_Help()
{
	system("cls");
	File_Open(HELP_SCREEN_PATH);
}

void New_Game()
{
	std::string str;

	system("cls");
	std::cout << "1P or 2P? : ";
	std::cin >> str;
	if (str == "1P")
	{
		Player player1 = Player();
		Create_Player(player1, "player1");
		Play_Game_1P();
	}
	else
	{
		Player player1 = Player();
		Player player2 = Player();
		Create_Player(player1, "player1");
		Create_Player(player2, "player2");
		Play_Game_2P();
	}
}

void Load_Game()
{
	//select 1p or 2p
	//input ID
	//Data Load
	//Play_Game_1P() or Play_Game_2P()
}

void Play_Game_1P()
{
	system("cls");
	std::cout << "1P Start\n";
	File_Open(GAMEBOX_1P_PATH);
	
}

void Play_Game_2P()
{
	system("cls");
	std::cout << "2P Start\n";
	File_Open(GAMEBOX_2P_PATH);
}