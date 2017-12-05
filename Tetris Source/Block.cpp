/*
	Block.cpp
	Defines the methods and members of the Block class.
*/

#pragma once
#include "constants.h"
#include "bgi\graphics.h"
#include "Block.h"

//Default Block constructor
Block::Block(){
	x = 0;
	y = 0;
	xLength = BLOCK_LENGTH;
	yLength = BLOCK_LENGTH;
	blockColor = DEFAULT_BLOCK_COLOR;
}

//Block constructor based on initial position
Block::Block(int xPosition, int yPosition){
	x = xPosition;
	y = yPosition;
	xLength = BLOCK_LENGTH;
	yLength = BLOCK_LENGTH;
	blockColor = DEFAULT_BLOCK_COLOR;
}

//Block constructor based on initial position and color
Block::Block(int xPosition, int yPosition, int color){
	x = xPosition;
	y = yPosition;
	xLength = BLOCK_LENGTH;
	yLength = BLOCK_LENGTH;
	blockColor = color;
}

//Draws the Block instance as a square polygon, using winbgim
void Block::draw(){
	setcolor(blockColor);
	setfillstyle(SOLID_FILL, blockColor);
	int vertices[4 * 2] = { x, y, x + xLength, y, x + xLength, y + yLength, x, y + yLength };
	fillpoly(4, vertices);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	rectangle(x, y, x + xLength, y + yLength);
}

//Moves the Block instance left by decrementing its x position by the block length
void Block::moveLeft(){
	x -= BLOCK_LENGTH;
}

//Moves the Block instance right by incrementing its x position by the block length
void Block::moveRight(){
	x += BLOCK_LENGTH;
}

//Moves the Block instance up by decrementing its y position by the block length
//Note: it is decremented for upward movement due to the (reverse) vertical orientation of winbgim
void Block::moveUp(){
	y -= BLOCK_LENGTH;
}

//Moves the Block instance up by incrementing its y position by the block length
//Note: it is incremented for downward movement due to the (reverse) vertical orientation of winbgim
void Block::moveDown(){
	y += BLOCK_LENGTH;
}

//Returns the x position of the Block instance
int Block::getX(){
	return x;
}

//Returns the y position of the Block instance
int Block::getY(){
	return y;
}

//Returns the horizontal length of the Block instance
int Block::getXLength(){
	return xLength;
}

//Returns the vertical length of the Block instance
int Block::getYLength(){
	return yLength;
}

//Returns the color of the Block instance
int Block::getColor(){
	return blockColor;
}

//Sets the x position of the Block instance
void Block::setX(int xNew){
	x = xNew;
}

//Sets the y position of the Block instance
void Block::setY(int yNew){
	y = yNew;
}

//Sets the horizontal length of the Block instance
void Block::setXLength(int newLength){
	xLength = newLength;
}

//Sets the vertical length of the Block instance
void Block::setYLength(int newLength){
	yLength = newLength;
}

//Sets the color of the Block instance
void Block::setColor(int newColor){
	blockColor = newColor;
}
