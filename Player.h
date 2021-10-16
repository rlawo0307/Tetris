#pragma once

#include <iostream>
#include <string>

#define INPUT_ID_PATH "res/input_ID.txt"

#define ID_X 3
#define ID_Y 6

class Player
{
private:
	File file;
	Cursor cs;
	std::string ID;

public:
	//int score;

	Player()
	{
		this->ID = Input_ID();
		//score = 0;
	}

	std::string Input_ID()
	{
		std::string str;
		char key = ' ';

		file.Print_File(INPUT_ID_PATH, ID_X, ID_Y);
		cs.Cursor_Move(ID_X + 10, ID_Y+2);
		std::cin >> str;
		return str;
	}

	std::string Get_ID()
	{
		std::string tmp;
		tmp.append(ID);
		return tmp;
	}
};

