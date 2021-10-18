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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
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

	bool Read_File(std::string ID, int* score, Data& data)
	{
		std::string path = "./save/";
		std::string tmp;
		char c;

		path = path + ID + ".txt";
		ifs.open(path);
		if (!ifs.is_open())
		{
			cs.Cursor_Move(BOX_X, BOX_Y+25);
			std::cout << "    *File Open Fail\n";
			return false;
		}
		ifs >> tmp;
		if (tmp != ID)
		{
			std::cout << "File Open Fail\n";
			return false;
		}
		
		ifs >> tmp;
		*score = std::stoi(tmp);

		ifs >> tmp;
		data.falling_speed = std::stoi(tmp);
		
		ifs.get(c);
		for (int i = 0; i < BOARD_COL; i++)
			for (int j = 0; j < BOARD_ROW; j++)
			{
				ifs.get(c);
				data.board[i][j] = c - '0';
			}

		ifs.get(c);
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
			{
				ifs.get(c);
				data.cur_block[i][j] = c - '0';
			}

		ifs.get(c);
		for (int i = 0; i < BLOCK_COL; i++)
			for (int j = 0; j < BLOCK_ROW; j++)
			{
				ifs.get(c);
				data.next_block[i][j] = c - '0';
			}

		ifs >> tmp;
		data.top = std::stoi(tmp);

		ifs >> tmp;
		data.block_x = std::stoi(tmp);

		ifs >> tmp;
		data.block_y = std::stoi(tmp);

		ifs.close();
		return true;
	}

	void Write_File(std::string& ID, int score, Data& data)
	{
		std::string path = "./save/";

		path = path + ID + ".txt";
		ofs.open(path);
		if (!ofs.is_open())
		{
			std::cout << "File Open Fail\n";
			return;
		}
		ofs << ID << std::endl;
		ofs <<  score << std::endl;
		ofs << data.falling_speed << std::endl;
		for (int i = 0; i < BOARD_COL; i++)
		{
			for (int j = 0; j < BOARD_ROW; j++)
				ofs << data.board[i][j];
		}
		ofs << "\n";
		for (int i = 0; i < BLOCK_COL; i++)
		{
			for (int j = 0; j < BLOCK_ROW; j++)
				ofs << data.cur_block[i][j];
		}
		ofs << "\n";
		for (int i = 0; i < BLOCK_COL; i++)
		{
			for (int j = 0; j < BLOCK_ROW; j++)
				ofs << data.next_block[i][j];
		}
		ofs << "\n";
		ofs << data.top << std::endl;
		ofs << data.block_x << std::endl;
		ofs << data.block_y << std::endl;
		ofs.close();
	}
};