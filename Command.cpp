#include <iostream>
#include <string>
#include "Command.h"
#include "Class.h"
#include "Func.h"

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
	std::cout << str[0] << std::endl;
	if (str == "1P")
	{
		Player player1 = Player();
		Play_Game_1P(player1);
	}
	else
	{
		Player player1 = Player();
		Player player2 = Player();
		Play_Game_2P(player1, player2);
	}
}

void Load_Game()
{
	//select 1p or 2p
	//input ID
	//Data Load
	//Play_Game_1P() or Play_Game_2P()
}

void Play_Game_1P(Player& p1)
{
	system("cls");
	std::cout << "1P Start\n";
	File_Open(GAMEBOX_1P_PATH);
}

void Play_Game_2P(Player& p1, Player& p2)
{
	system("cls");
	std::cout << "2P Start\n";
	File_Open(GAMEBOX_2P_PATH);
}