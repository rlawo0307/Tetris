#pragma once

#include <iostream>
#include <fstream>
#include <string>

class File
{
private:
	std::ifstream ifs;

public:
	void File_Open(const std::string path)
	{
		std::string tmp;

		ifs.open(path);
		if (!ifs.is_open())
		{
			std::cout << "File Open Fail\n";
			return;
		}
		while (getline(ifs, tmp))
			std::cout << tmp << std::endl;
		ifs.close();
	}
};