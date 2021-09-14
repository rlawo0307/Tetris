#include <iostream>
#include <random>
#include "Class.h"
#include "Game.h"

void Create_Player(Player& player, const std::string str)
{
	std::cout << str << " ID : ";
	std::cin >> player.ID;
	player.score = 0;
	player.data = Game_Setting();
	player.data.falling_speed = 1.0; // default
	player.data.i_next_block = player.data.c_next_block = Rand_Next_Block();
}

int Rand_Next_Block()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 6);
	return dis(gen);
}
