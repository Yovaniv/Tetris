/*
	LTetrimino.cpp
	Defines the methods and members of the LTetrimino class.
*/
#include "constants.h"
#include "Tetriminos.h"

//Default LTetrimino constructor
LTetrimino::LTetrimino(){
	blockCount = 4;
	blocks = new Block[blockCount];
	blockColor = L_TETRIMINO_COLOR;
	x = BLOCKS_PER_GRID_WIDTH*BLOCK_LENGTH / 2;
	y = 0;
	blocks[0] = Block(x, y, blockColor);
	blocks[1] = Block(x, y + BLOCK_LENGTH, blockColor);
	blocks[2] = Block(x, y + 2 * BLOCK_LENGTH, blockColor);
	blocks[3] = Block(x + BLOCK_LENGTH, y + 2 * BLOCK_LENGTH, blockColor);
	type = L_TETRIMINO;
	orientation = TOP_FACING_TOP;
}

//LTetrimino destructor, blocks has to be deleted here due to the pure virtual destructor of the Tetrimino Class
LTetrimino::~LTetrimino(){
	delete[] blocks;
}

//Rotates the blocks of the LTetrimino instance about block[1]
void LTetrimino::rotate(){
	switch (orientation){
	case TOP_FACING_TOP:
		blocks[0].moveRight();
		blocks[0].moveDown();
		blocks[2].moveLeft();
		blocks[2].moveUp();
		blocks[3].moveLeft();
		blocks[3].moveLeft();
		orientation = TOP_FACING_RIGHT;
		break;
	case TOP_FACING_RIGHT:
		blocks[0].moveLeft();
		blocks[0].moveDown();
		blocks[2].moveRight();
		blocks[2].moveUp();
		blocks[3].moveUp();
		blocks[3].moveUp();
		orientation = TOP_FACING_BOTTOM;
		break;
	case TOP_FACING_BOTTOM:
		blocks[0].moveLeft();
		blocks[0].moveUp();
		blocks[2].moveRight();
		blocks[2].moveDown();
		blocks[3].moveRight();
		blocks[3].moveRight();
		orientation = TOP_FACING_LEFT;
		break;
	case TOP_FACING_LEFT:
		blocks[0].moveRight();
		blocks[0].moveUp();
		blocks[2].moveLeft();
		blocks[2].moveDown();
		blocks[3].moveDown();
		blocks[3].moveDown();
		orientation = TOP_FACING_TOP;
		break;
	default:
		break;
	}
}

//Returns a pointer to a deep-copy Tetrimino instance of the calling LTetrimino instance
Tetrimino* LTetrimino::clone(){
	Tetrimino* cloned = new LTetrimino();

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

//Sets the x position of the LTetrimino and the x position of its blocks
//TODO: Add orientation specificity, this currently only works for Tetriminos with TOP_FACING_TOP orientation
void LTetrimino::setX(int newX){
	x = newX;
	blocks[0].setX(x);
	blocks[1].setX(x);
	blocks[2].setX(x);
	blocks[3].setX(x+ BLOCK_LENGTH);
}

//Sets the y position of the LTetrimino and the y position of its blocks
//TODO: Add orientation specificity, this currently only works for Tetriminos with TOP_FACING_TOP orientation
void LTetrimino::setY(int newY){
	y = newY;
	blocks[0].setY(y);
	blocks[1].setY(y + BLOCK_LENGTH);
	blocks[2].setY(y + 2 * BLOCK_LENGTH);
	blocks[3].setY(y + 2 * BLOCK_LENGTH);
}