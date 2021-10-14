#pragma once

#include <iostream>
#include <string>

class Player
{
private:
	std::string ID;

public:
	int score;

	Player(int num)
	{
		this->ID = Input_ID();
		score = 0;
	}

	const std::string Input_ID()
	{
		std::string str;
		std::cout << "Player ID : ";
		std::cin >> str;
		return str;
	}
};

