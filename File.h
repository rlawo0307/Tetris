#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Cursor.h"

class File
{
private:
	Cursor cs;
	std::ifstream ifs;

public:
	File()
	{
		cs = Cursor();
	}

	void File_Open(const std::string path, int x, int y)
	{
		std::string tmp;

		ifs.open(path);
		if (!ifs.is_open())
		{
			std::cout << "File Open Fail\n";
			return;
		}
		while (getline(ifs, tmp))
		{
			cs.Cursor_Move(x, y++);
			std::cout << tmp << std::endl;
		}
		ifs.close();
	}
};