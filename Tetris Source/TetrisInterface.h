/*
	TetrisInterface.h
	Declares the TetrisInterface class prototype. The Interface class contains a BockOverlay
	instance to hold and handle Tetriminos that have reached the bottom of the play area. It 
	also handles the score, level, drop speed,  and visual graphics of the game.
*/

#pragma once
#include "constants.h"
#include "Tetrimino.h"
#include "Timer.h"
#include "BlockOverlay.h"

class TetrisInterface{
public:
	TetrisInterface();
	TetrisInterface(int time);
	//~TetrisInterface();
	void draw();
	void clear();
	bool stillPlaying();
	void setPlaying(bool playState);
	bool isGameOver();
	void setGameOver(bool isGameOver);
	int getTimeDelay();
	bool isTimeToMove();
	void resetDelayer();
	bool isPaused();
	void setPause(bool pause);
	void draw(Tetrimino* current, Tetrimino* typeSource);
	void drawGameOver();
	void drawPaused();
	void display();
	bool tetriminoCanRotate(Tetrimino* current);
	bool tetriminoCanMoveLeft(Tetrimino* current);
	bool tetriminoCanMoveRight(Tetrimino* current);
	bool tetriminoCanMoveDown(Tetrimino* current);
	bool tetriminoOverlapsBlocks(Tetrimino* current);
	void addTetrimino(Tetrimino* current);
	void clearLines();
	void addToScore(int addition);
	void addToLinesCleared(int addition);
	int getScore();
	int getLinesCleared();
	int getLevel();
	void setScore(int newScore);
	void setLinesCleared(int newClear);
	void setLevel(int newLevel);
	bool pollEvent();
	sf::Keyboard::Key getEventKey();
	void clearDisplay();
private:
	int score, linesCleared, level;
	bool playing, gameOver, paused;
	Timer timer, delayer, pauser;
	BlockOverlay blockOverlay;
	sf::RenderWindow mainWindow;
	sf::Event currentEvent;
};
