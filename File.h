#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Cursor.h"
#include "var.h"

class File
{
private:
	Cursor cs;
	std::ifstream ifs;
	std::ofstream ofs;

public:

	void Print_File(const std::string path, int x, int y)
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

	void Clear_File(const std::string path, int x, int y)
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
			for (int i = 0; i < size(tmp); i++)
				std::cout << " ";
		}
		ifs.close();
	}

	void Write_File(std::string ID, int score, Data& data)
	{
		std::string path = "./save/";

		path = path + ID + ".txt";

		ofs.open(path);
		if (!ofs.is_open())
		{
			std::cout << "File Open Fail\n";
			return;
		}
		ofs << "ID : " << ID << std::endl;
		ofs << "score : " << score << std::endl;
		ofs << "falling speed : " << data.falling_speed << std::endl;
		ofs << "i_next_block : " << data.i_next_block << std::endl;
		ofs << "board : \n";
		for (int i = 0; i < BOARD_COL; i++)
		{
			for (int j = 0; j < BOARD_ROW; j++)
				ofs << data.board[i][j] << " ";
			ofs << "\n";
		}
		ofs << "cur_block : \n";
		for (int i = 0; i < BLOCK_COL; i++)
		{
			for (int j = 0; j < BLOCK_ROW; j++)
				ofs << data.cur_block[i][j] << " ";
			ofs << "\n";
		}
		ofs << "top : " << data.top << std::endl;
		ofs.close();
	}
};