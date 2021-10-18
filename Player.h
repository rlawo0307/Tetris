#pragma once

#include <iostream>
#include <string>
#include "var.h"

#define INPUT_ID_PATH "res/input_ID.txt"

#define ID_X BOX_X
#define ID_Y BOX_Y+20

class Player
{
private:
	File file;
	Cursor cs;
	std::string ID;
	int score;

public:
	Player()
	{
		this->ID = Input_ID();
	}

	std::string Input_ID()
	{
		std::string str;

		file.Print_File(INPUT_ID_PATH, ID_X, ID_Y);
		cs.Cursor_Move(ID_X + 10, ID_Y+2);
		std::cin >> str;
		return str;
	}

	std::string Get_ID()
	{
		return ID;
	}

	void Set_Score(int score)
	{
		this->score = score;
	}

	int Get_Score()
	{
		return score;
	}
};

