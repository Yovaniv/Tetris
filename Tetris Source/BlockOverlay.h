/*
	BlockOverlay.h
	Declares the BlockOverlay class prototype. The BlockOverlay class contains a 
	set of Block instances that have been added from the tetriminos that can no 
	longer move down. The grid array is used to track which locations on the play 
	area already contain a block.
*/

#pragma once
#include "constants.h"
#include "bgi\graphics.h"
#include "Block.h"
#include "Tetrimino.h"

class BlockOverlay{
public:
	BlockOverlay();
	BlockOverlay(Block* newBlocks, int count);
	~BlockOverlay();
	void draw();
	void clear();
	void addTetriminoBlocks(Tetrimino* blockSource);
	void clearGrid();
	bool updateGrid();
	bool linesPresent();
	void clearLowestLine();
	bool tetriminoCanRotate(Tetrimino* current);
	bool tetriminoCanMoveLeft(Tetrimino* current);
	bool tetriminoCanMoveRight(Tetrimino* current);
	bool tetriminoCanMoveDown(Tetrimino* current);
	bool checkForOverlap(Tetrimino* tetrimino);
	bool withinBoundary(Tetrimino* tetrimino);
private:
	Block* blocks;
	int blockCount;
	bool grid[BLOCKS_PER_GRID_WIDTH][BLOCKS_PER_GRID_HEIGHT];
};