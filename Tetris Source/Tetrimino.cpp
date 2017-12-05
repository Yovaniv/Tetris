/*
	Tetrimino.cpp
	Defines the methods and members of the Tetrimino class.
*/

#include "constants.h"
#include "bgi\graphics.h"
#include "Tetrimino.h"

//Default Tetrimino constructor
Tetrimino::Tetrimino(){
}

//Default Tetrimino deconstructor
//Declared as a pure virtual function, deconstruction of blocks pointer to be handled by derived classes
Tetrimino::~Tetrimino(){
}

//Draws the tetrimino by iterating through its block instances and calling their draw method
void Tetrimino::draw(){
	for (int i = 0; i < blockCount; i++){
		blocks[i].draw();
	}
}

//Moves the tetrimino left by iterating through its block instances and calling their moveLeft methods
void Tetrimino::moveLeft(){
	for (int i = 0; i < blockCount; i++){
		blocks[i].moveLeft();
	}
}

//Moves the tetrimino Right by iterating through its block instances and calling their moveRight methods
void Tetrimino::moveRight(){
	for (int i = 0; i < blockCount; i++){
		blocks[i].moveRight();
	}
}

//Moves the tetrimino up by iterating through its block instances and calling their moveUp methods
//Note: this method should not normally be called
void Tetrimino::moveUp(){
	for (int i = 0; i < blockCount; i++){
		blocks[i].moveUp();
	}
}

//Moves the tetrimino down by iterating through its block instances and calling their moveDown methods
void Tetrimino::moveDown(){
	for (int i = 0; i < blockCount; i++){
		blocks[i].moveDown();
	}
}

//Returns the number of Block instances in the calling Tetrimino instance 
int Tetrimino::getBlockCount(){
	return blockCount;
}

//Returns the Block instance at the index of the calling Tetrimino instance 
Block Tetrimino::getBlock(int index){
	return blocks[index];
}

//Returns the type of the calling Tetrimino instance
TetriminoType Tetrimino::getType(){
	return type;
}

//Sets the x position of the Tetrimino instance
void Tetrimino::setX(int newX){
	x = newX;
}

//Sets the y position of the Tetrimino instance
void Tetrimino::setY(int newY){
	y = newY;
}

//Sets the x and y position of the Tetrimino instance
void Tetrimino::setXY(int newX, int newY){
	Tetrimino::setX(newX);
	Tetrimino::setY(newY);
}

//Sets the block color of the Tetrimino instance
void Tetrimino::setBlockColor(int newBlockColor){
	blockColor = newBlockColor;
}

//Sets the number of Block instances in the Tetrimino instance
void Tetrimino::setBlockCount(int newCount){
	blockCount = newCount;
}

//Sets the Block instance at the index in the Tetrimino instance
void Tetrimino::setBlock(int index, Block newBlock){
	blocks[index] = newBlock;
}

//Initiates the number of Block instances in the Tetrimino instance
void Tetrimino::setBlocks(){
	blocks = new Block[blockCount];
}

//Sets the type of the Tetrimino instance
void Tetrimino::setType(TetriminoType newType){
	type = newType;
}

//Sets the orientation of the Tetrimino instance
void Tetrimino::setOrientation(TetriminoOrientation newOrientation){
	orientation = newOrientation;
}