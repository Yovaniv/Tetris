/*
	Block.h
	Declares the Block class prototype. Block objects are drawable objects that can be moved around.
*/

#pragma once
#include "SFML\Graphics.hpp"

class Block{
public:
	Block();
	Block(int xPosition, int yPosition);
	Block(int xPosition, int yPosition, sf::Color color);
	void draw();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	int getX();
	int getY();
	int getXLength();
	int getYLength();
	sf::Color getColor();
	void setX(int xNew);
	void setY(int yNew);
	void setXLength(int newLength);
	void setYLength(int newLength);
	void setColor(sf::Color newColor);
	sf::RectangleShape asRectangleShape();
private:
	int x;
	int xLength;
	int y;
	int yLength;
	sf::Color blockColor;
};