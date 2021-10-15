#pragma once

#include <iostream>
#include <string>

#define INPUT_ID "res/input_ID.txt"

#define ID_X 30
#define ID_Y 6
class Player
{
private:
	File file;
	Cursor cs;
	std::string ID;

public:
	int score;

	Player(int num)
	{
		file = File();
		cs = Cursor();
		this->ID = Input_ID();
		score = 0;
	}

	const std::string Input_ID()
	{
		std::string str;

		file.Print_File(INPUT_ID, ID_X, ID_Y);
		cs.Cursor_Move(ID_X + 10, ID_Y+2);
		std::cin >> str;
		return str;
	}
};

