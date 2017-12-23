/*
	Tetrimino.h
	Declares the abstract base Tetrimino class prototype. Tetrimino objects are
	the falling pieces in the Tetris program. They contain a set of Block 
	instances as well as type and orientation members.
*/

#pragma once
#include "Block.h"

class Tetrimino{
public:
	Tetrimino();
	virtual Tetrimino* clone() = 0;
	virtual ~Tetrimino() = 0;
	void draw();
	virtual void rotate() = 0;
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	int getBlockCount();
	Block getBlock(int index);
	TetriminoType getType();
	virtual void setX(int newX);
	virtual void setY(int newY);
	void setXY(int newX, int newY);
	void setBlockColor(sf::Color newBlockColor);
	void setBlockCount(int newCount);
	void setBlocks();
	void setBlock(int index, Block newBlock);
	void setType(TetriminoType newType);
	void setOrientation(TetriminoOrientation newOrientation);

protected:
	Block* blocks;
	int blockCount;
	sf::Color blockColor;
	int x, y;
	TetriminoType type;
	TetriminoOrientation orientation;
};
