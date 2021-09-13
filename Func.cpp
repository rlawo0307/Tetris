#include <iostream>
#include <string>
#include <fstream>
#include "Func.h"

void File_Open(const std::string path)
{
	std::string tmp;

	std::ifstream ifs;
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