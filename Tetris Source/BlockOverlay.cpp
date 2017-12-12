/*
	BlockOverlay.cpp
	Defines the methods and members of the BlockOverlay class.
*/

#pragma once
#include "BlockOverlay.h"

//Default BlockOverlay class constructor
BlockOverlay::BlockOverlay(){
	blocks = nullptr;
	blockCount = 0;
	this->clearGrid();
}

//Constructor that accepts a pointer to a set  of Block instances for initiation
BlockOverlay::BlockOverlay(Block* newBlocks, int count){
	blocks = new Block[count];
	for (int i = 0; i < blockCount; i++){
		blocks[i] = newBlocks[i];
	}
	blockCount = count;
	this->updateGrid();
}

//BlockOverlay Class Destructor
BlockOverlay::~BlockOverlay(){
	delete[] blocks;
}

//Draws the BlockOverlay instance by calling each Block instances draw method
void BlockOverlay::draw(){
	for (int i = 0; i < blockCount; i++){
		blocks[i].draw();
	}
}

//Deletes the block instances, sets the block count to zero, and calls the clearGrid method
//To be called when a new game is started
void BlockOverlay::clear(){
	delete[] blocks;
	blocks = nullptr;
	blockCount = 0;
	this->clearGrid();
}

//Adds the Block instances of a Tetrimino instance to the calling BlockOverlay instance
void BlockOverlay::addTetriminoBlocks(Tetrimino* blockSource){
	Block* tempBlocks = blocks;
	blocks = new Block[blockCount + blockSource->getBlockCount()];
	for (int i = 0; i < blockCount; i++){
		blocks[i] = tempBlocks[i];
	}
	delete[] tempBlocks;
	for (int i = 0; i < blockSource->getBlockCount(); i++){
		blocks[blockCount + i] = blockSource->getBlock(i);
	}
	blockCount = blockCount + blockSource->getBlockCount();
	this->updateGrid();
}

//Sets all boolean values in the grid array to false
void BlockOverlay::clearGrid(){
	for (int i = 0; i < BLOCKS_PER_GRID_WIDTH; i++){
		for (int j = 0; j < BLOCKS_PER_GRID_HEIGHT; j++){
			grid[i][j] = false;
		}
	}
}

//Iterates through all Block instances in the calling BlockOverlay instance,
//setting their corresponding location in the grid array as true, when false
//Returns false if two blocks have the same location
//Returns true when blocks have unique locations
bool BlockOverlay::updateGrid(){
	this->clearGrid();
	int indexX, indexY = 0;
	for (int i = 0; i < blockCount; i++){
		indexX = blocks[i].getX() / BLOCK_LENGTH;
		indexY = blocks[i].getY() / BLOCK_LENGTH;
		if (grid[indexX][indexY] == false){
			grid[indexX][indexY] = true;
		} else {
			return false;
		}
	}
	return true;
}

//Returns true when a complete horizontal line of blocks exists, otherwise returns false
bool BlockOverlay::linesPresent(){
	for (int i = BLOCKS_PER_GRID_HEIGHT - 1; i >= 0; i--){
		for (int j = 0; j < BLOCKS_PER_GRID_WIDTH; j++){
			if (grid[j][i] == false){
				break;
			}
			if (j == BLOCKS_PER_GRID_WIDTH - 1 && grid[j][i] == true){
				return true;
			}
		}
	}
	return false;
}

//Finds the lowest occuring line of blocks, then deletes blocks on that line
//Moves blocks down once, if they are above that line
void BlockOverlay::clearLowestLine(){
	int lowestLine = 0;
	int indexX = 0;
	int indexY = 0;
	for (int i = BLOCKS_PER_GRID_HEIGHT - 1; i >= 0 && i >= lowestLine; i--){
		for (int j = 0; j < BLOCKS_PER_GRID_WIDTH; j++){
			if (grid[j][i] == false){
				break;
			}
			if (j == BLOCKS_PER_GRID_WIDTH - 1 && grid[j][i] == true){
				lowestLine = i;
				break;
			}
		}
	}
	Block* tempBlocks = blocks;
	blocks = new Block[blockCount - BLOCKS_PER_GRID_WIDTH];
	int j = 0;
	for (int i = 0; i < blockCount; i++){
		indexY = tempBlocks[i].getY() / BLOCK_LENGTH;
		if (indexY > lowestLine){
			blocks[j] = tempBlocks[i];
			j++;
		}
		else if (indexY < lowestLine){
			tempBlocks[i].moveDown();
			blocks[j] = tempBlocks[i];
			j++;
		}
	}
	blockCount -= BLOCKS_PER_GRID_WIDTH;
	delete[] tempBlocks;
	this->updateGrid();
}

//Tests whether a Tetrimino instance will go out of boundary or overlap the BlockOverlay blocks, if it is rotated
//Returns true if a rotation will not cause the tetrimino to overlap or go out of bounds
bool BlockOverlay::tetriminoCanRotate(Tetrimino* current){
	Tetrimino* tempTetrimino = current->clone();
	tempTetrimino->rotate();
	if (withinBoundary(tempTetrimino)){
		return !checkForOverlap(tempTetrimino);
	} else {
		return false;
	}
}

//Tests whether a Tetrimino instance will go out of boundary or overlap the BlockOverlay blocks, when moved left
//Returns true if a left movement will not cause the tetrimino to overlap or go out of bounds
bool BlockOverlay::tetriminoCanMoveLeft(Tetrimino* current){
	Tetrimino* tempTetrimino = current->clone();
	tempTetrimino->moveLeft();
	if (withinBoundary(tempTetrimino)){
		return !checkForOverlap(tempTetrimino);
	} else {
		return false;
	}
}

//Tests whether a Tetrimino instance will go out of boundary or overlap the BlockOverlay blocks, when moved right
//Returns true if a right movement will not cause the tetrimino to overlap or go out of bounds
bool BlockOverlay::tetriminoCanMoveRight(Tetrimino* current){
	Tetrimino* tempTetrimino = current->clone();
	tempTetrimino->moveRight();
	if (withinBoundary(tempTetrimino)){
		return !checkForOverlap(tempTetrimino);
	} else {
		return false;
	}
}

//Tests whether a Tetrimino instance will go out of boundary or overlap the BlockOverlay blocks, when moved down
//Returns true if a downward movement will not cause the tetrimino to overlap or go out of bounds
bool BlockOverlay::tetriminoCanMoveDown(Tetrimino* current){
	Tetrimino* tempTetrimino = current->clone();
	tempTetrimino->moveDown();
	if (withinBoundary(tempTetrimino)){
		return !checkForOverlap(tempTetrimino);
	} else {
		return false;
	}
}

//Tests a Tetrimino instance for Block instances that overlap the blocks of the BlockOverlay instance
//Returns true if overlap occurs, otherwise returns false 
bool BlockOverlay::checkForOverlap(Tetrimino* tetrimino){
	int x, y;
	for (int i = 0; i < tetrimino->getBlockCount(); i++){
		x = tetrimino->getBlock(i).getX() / BLOCK_LENGTH;
		y = tetrimino->getBlock(i).getY() / BLOCK_LENGTH;
		if (grid[x][y] == true){
			return true;
		}
	}
	return false;
}

//Tests whether a Tetrimino instance is within the play area boundaries
//Returns false if a block is outside the boundaries, otherwise returns true
bool BlockOverlay::withinBoundary(Tetrimino* tetrimino){
	int x, y;
	for (int i = 0; i < tetrimino->getBlockCount(); i++){
		x = tetrimino->getBlock(i).getX();
		y = tetrimino->getBlock(i).getY();
		if (!(x >= 0 && x <= BLOCK_GRID_WIDTH - BLOCK_LENGTH && y >= 0 && y <= HEIGHT - BLOCK_LENGTH)){
			return false;
		}
	}
	return true;
}

int BlockOverlay::getBlockCount(){
	return blockCount;
}

Block BlockOverlay::getBlock(int index){
	return blocks[index];
}