/*
	ITetrimino.cpp
	Defines the methods and members of the ITetrimino class.
*/

#include "constants.h"
#include "Tetriminos.h"

//Default ITetrimino constructor
ITetrimino::ITetrimino(){
	blockCount = 4;
	blocks = new Block[blockCount];
	blockColor = I_TETRIMINO_COLOR;
	x = BLOCKS_PER_GRID_WIDTH*BLOCK_LENGTH / 2;
	y = 0;
	blocks[0] = Block(x, y, blockColor);
	blocks[1] = Block(x, y + BLOCK_LENGTH, blockColor);
	blocks[2] = Block(x, y + 2 * BLOCK_LENGTH, blockColor);
	blocks[3] = Block(x, y + 3 * BLOCK_LENGTH, blockColor);
	type = I_TETRIMINO;
	orientation = TOP_FACING_TOP;
}

//ITetrimino destructor, blocks has to be deleted here due to the pure virtual destructor of the Tetrimino Class
ITetrimino::~ITetrimino(){
	delete[] blocks;
}

//Rotates the blocks of the ZTetrimino instance about block[1]
void ITetrimino::rotate(){
	switch (orientation){
	case TOP_FACING_TOP:
	case TOP_FACING_BOTTOM:
		blocks[0].moveRight();
		blocks[0].moveDown();
		blocks[2].moveLeft();
		blocks[2].moveUp();
		blocks[3].moveLeft();
		blocks[3].moveLeft();
		blocks[3].moveUp();
		blocks[3].moveUp();
		orientation = TOP_FACING_RIGHT;
		break;
	case TOP_FACING_LEFT:
	case TOP_FACING_RIGHT:
		blocks[0].moveLeft();
		blocks[0].moveUp();
		blocks[2].moveRight();
		blocks[2].moveDown();
		blocks[3].moveRight();
		blocks[3].moveRight();
		blocks[3].moveDown();
		blocks[3].moveDown();
		orientation = TOP_FACING_TOP;
		break;
	default:
		break;
	}
}

//Returns a pointer to a deep-copy Tetrimino instance of the calling ITetrimino instance
Tetrimino* ITetrimino::clone(){
	Tetrimino* cloned = new ITetrimino();

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

//Sets the x position of the ITetrimino and the x position of its blocks
//TODO: Add orientation specificity, this currently only works for Tetriminos with TOP_FACING_TOP orientation
void ITetrimino::setX(int newX){
	x = newX;
	for (int i = 0; i < blockCount; i++){
		blocks[i].setX(newX);
	}
}

//Sets the y position of the ITetrimino and the y position of its blocks
//TODO: Add orientation specificity, this currently only works for Tetriminos with TOP_FACING_TOP orientation
void ITetrimino::setY(int newY){
	y = newY;
	for (int i = 0; i < blockCount; i++){
		blocks[i].setY(newY+i*BLOCK_LENGTH);
	}
}