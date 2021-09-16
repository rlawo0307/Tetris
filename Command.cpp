#include <iostream>
#include <string>
#include "Command.h"
#include "Class.h"
#include "Func.h"
#include <windows.h> // Sleep()

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
	double speed = 1000 * p1.data.falling_speed;
	bool game = true;
	int i;

	system("cls");
	std::cout << "1P Start\n";
	File_Open(GAMEBOX_1P_PATH);

	while (game)
	{
		i = 0;
		p1.data.Rand_Next_Block();
		while(i <= BOARD_COL - CUR_BLOCK_COL) //Before reach bottom of borad
		{
			if (p1.data.Check_Next_Line(i)) //Before reach top block
			{
				p1.data.Change_Board(i);
				Key_Input();
				p1.data.Print_Board();
				Sleep(speed);
				i++;
			}
			else
				break;
		}
		if (i == 0)
		{
			std::cout << "Game Over\n";
			game = false;
		}
	}
}

void Play_Game_2P(Player& p1, Player& p2)
{
	system("cls");
	std::cout << "2P Start\n";
	File_Open(GAMEBOX_2P_PATH);
}