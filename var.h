#pragma once

#define BOARD_COL 20
#define BOARD_ROW 10
#define BLOCK_COL 4
#define BLOCK_ROW 4

#define BOX_X 0
#define BOX_Y 0

typedef struct DATA
{
	double falling_speed;
	int board[BOARD_COL][BOARD_ROW];
	int cur_block[BLOCK_COL][BLOCK_ROW];
	int next_block[BLOCK_COL][BLOCK_ROW];
	int top;
	int block_x, block_y;
}Data;