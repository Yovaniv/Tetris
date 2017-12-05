/*
	ZTetrimino.cpp
	Defines the methods and members of the ZTetrimino class.
*/

#include "constants.h"
#include "Tetriminos.h"

//Default ZTetrimino constructor
ZTetrimino::ZTetrimino(){
	blockCount = 4;
	blocks = new Block[blockCount];
	blockColor = Z_TETRIMINO_COLOR;
	x = BLOCKS_PER_GRID_WIDTH*BLOCK_LENGTH / 2;
	y = 0;
	blocks[0] = Block(x, y, blockColor);
	blocks[1] = Block(x + BLOCK_LENGTH, y, blockColor);
	blocks[2] = Block(x + BLOCK_LENGTH, y + BLOCK_LENGTH, blockColor);
	blocks[3] = Block(x + 2 * BLOCK_LENGTH, y + BLOCK_LENGTH, blockColor);
	type = Z_TETRIMINO;
	orientation = TOP_FACING_TOP;
}

//ZTetrimino destructor, blocks has to be deleted here due to the pure virtual destructor of the Tetrimino Class
ZTetrimino::~ZTetrimino(){
	delete[] blocks;
}

//Rotates the blocks of the ZTetrimino instance about block[1]
void ZTetrimino::rotate(){
	switch (orientation){
	case TOP_FACING_TOP:
	case TOP_FACING_BOTTOM:
		blocks[0].moveRight();
		blocks[0].moveUp();
		blocks[2].moveLeft();
		blocks[2].moveUp();
		blocks[3].moveLeft();
		blocks[3].moveLeft();
		orientation = TOP_FACING_RIGHT;
		break;
	case TOP_FACING_RIGHT:
	case TOP_FACING_LEFT:
		blocks[0].moveLeft();
		blocks[0].moveDown();
		blocks[2].moveRight();
		blocks[2].moveDown();
		blocks[3].moveRight();
		blocks[3].moveRight();
		orientation = TOP_FACING_BOTTOM;
		break;
	default:
		break;
	}
}

//Returns a pointer to a deep-copy Tetrimino instance of the calling ZTetrimino instance
Tetrimino* ZTetrimino::clone(){
	Tetrimino* cloned = new ZTetrimino();

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

//Sets the x position of the ZTetrimino and the x position of its blocks
//TODO: Add orientation specificity, this currently only works for Tetriminos with TOP_FACING_TOP orientation
void ZTetrimino::setX(int newX){
	x = newX;
	blocks[0].setX(x);
	blocks[1].setX(x+BLOCK_LENGTH);
	blocks[2].setX(x+BLOCK_LENGTH);
	blocks[3].setX(x+2*BLOCK_LENGTH);
}

//Sets the y position of the ZTetrimino and the y position of its blocks
//TODO: Add orientation specificity, this currently only works for Tetriminos with TOP_FACING_TOP orientation
void ZTetrimino::setY(int newY){
	y = newY;
	blocks[0].setY(y);
	blocks[1].setY(y);
	blocks[2].setY(y+BLOCK_LENGTH);
	blocks[3].setY(y+BLOCK_LENGTH);
}