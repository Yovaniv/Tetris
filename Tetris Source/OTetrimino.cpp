/*
	OTetrimino.cpp
	Defines the methods and members of the OTetrimino class.
*/

#include "constants.h"
#include "Tetriminos.h"

//Default OTetrimino constructor
OTetrimino::OTetrimino(){
	blockCount = 4;
	blocks = new Block[blockCount];
	blockColor = O_TETRIMINO_COLOR;
	x = BLOCKS_PER_GRID_WIDTH*BLOCK_LENGTH / 2;
	y = 0;
	blocks[0] = Block(x, y, blockColor);
	blocks[1] = Block(x - BLOCK_LENGTH, y, blockColor);
	blocks[2] = Block(x - BLOCK_LENGTH, y + BLOCK_LENGTH, blockColor);
	blocks[3] = Block(x, y + BLOCK_LENGTH, blockColor);
	type = O_TETRIMINO;
	orientation = TOP_FACING_TOP;
}

//OTetrimino destructor, blocks has to be deleted here due to the pure virtual destructor of the Tetrimino Class
OTetrimino::~OTetrimino(){
	delete[] blocks;
}

//Method is empty due to all four TetriminoOrientations being equivalent for an OTetrimino 
void OTetrimino::rotate(){
}

//Returns a pointer to a deep-copy Tetrimino instance of the calling OTetrimino instance
Tetrimino* OTetrimino::clone(){
	Tetrimino* cloned = new OTetrimino();

	cloned->setBlockCount(blockCount);
	cloned->setBlockColor(blockColor);
	cloned->setBlocks();
	for (int i = 0; i < cloned->getBlockCount(); i++){
		cloned->setBlock(i, this->getBlock(i));
	}
	cloned->Tetrimino::setXY(x, y);
	cloned->setType(type);
	cloned->setOrientation(orientation);
	return cloned;
}

//Sets the x position of the OTetrimino and the x position of its blocks
//TODO: Add orientation specificity, this currently only works for Tetriminos with TOP_FACING_TOP orientation
void OTetrimino::setX(int newX){
	x = newX;
	blocks[0].setX(x);
	blocks[1].setX(x - BLOCK_LENGTH);
	blocks[2].setX(x - BLOCK_LENGTH);
	blocks[3].setX(x);
}

//Sets the y position of the OTetrimino and the y position of its blocks
//TODO: Add orientation specificity, this currently only works for Tetriminos with TOP_FACING_TOP orientation
void OTetrimino::setY(int newY){
	y = newY;
	blocks[0].setY(y);
	blocks[1].setY(y);
	blocks[2].setY(y + BLOCK_LENGTH);
	blocks[3].setY(y + BLOCK_LENGTH);
}