/*
	TetrisInterface.cpp
	Defines the methods and members of the TetrisInterface class.
*/

#include "constants.h"
#include "SFML\Graphics.hpp"
#include "Tetrimino.h"
#include "TetrisInterface.h"

//Default TetrisInterface constructor
TetrisInterface::TetrisInterface(){
	score = 0;
	linesCleared = 0;
	level = 1;
	playing = true;
	gameOver = false;
	paused = false;
	mainWindow.create(sf::VideoMode(WIDTH, HEIGHT), "Tetris");
	mainWindow.clear(BACKGROUND_COLOR);
	mainWindow.setVerticalSyncEnabled(true);
	blockOverlay = BlockOverlay();
	timer = Timer();
	delayer = Timer();
	pauser = Timer();
}

//TetrisInterface constructor that instantiates the instance using a reference time for all the Timers
TetrisInterface::TetrisInterface(int time){
	score = 0;
	linesCleared = 0;
	level = 1;
	timer = Timer(time);
	delayer = Timer(time);
	pauser = Timer(time);
	playing = true;
	gameOver = false;
	paused = false;
	blockOverlay = BlockOverlay();
	mainWindow.create(sf::VideoMode(WIDTH, HEIGHT), "Tetris");
	mainWindow.clear(BACKGROUND_COLOR);
}


/*TetrisInterface::~TetrisInterface(){
	delete mainWindow;
}*/

//Draws the side display panel using winbgim 
void TetrisInterface::draw(){
	sf::RectangleShape panel;
	panel.setSize(sf::Vector2f(INTERFACE_WIDTH, INTERFACE_HEIGHT) - sf::Vector2f(INTERFACE_OUTLINE_THICKNESS, INTERFACE_OUTLINE_THICKNESS));
	panel.setFillColor(INTERFACE_COLOR);
	panel.setOutlineColor(INTERFACE_OUTLINE_COLOR);
	panel.setOutlineThickness(INTERFACE_OUTLINE_THICKNESS);
	panel.setPosition(sf::Vector2f(WIDTH - INTERFACE_WIDTH + INTERFACE_OUTLINE_THICKNESS, 0));
	mainWindow.draw(panel);

	sf::Font font;
	font.loadFromFile("resources/arial.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(FONT_SIZE);
	text.setFillColor(FONT_COLOR);
	char stringBuffer[30] = { '\0' };
	sprintf_s(stringBuffer, "Next Tetrimino");
	text.setString(stringBuffer);
	text.setPosition(BLOCK_GRID_WIDTH + (INTERFACE_WIDTH - text.getLocalBounds().width) / 2, 0);
	mainWindow.draw(text);

	sprintf_s(stringBuffer, "Level: %i", level);
	text.setPosition(BLOCK_GRID_WIDTH + 5, HEIGHT / 2);
	text.setString(stringBuffer);
	mainWindow.draw(text);

	sprintf_s(stringBuffer, "Lines: %i", linesCleared);
	text.setPosition(BLOCK_GRID_WIDTH + 5, HEIGHT / 2 + FONT_SIZE);
	text.setString(stringBuffer);
	mainWindow.draw(text);

	sprintf_s(stringBuffer, "Score: %i", score);
	text.setPosition(BLOCK_GRID_WIDTH + 5, HEIGHT / 2 + 2 * FONT_SIZE);
	text.setString(stringBuffer);
	mainWindow.draw(text);

	int currentTime = timer.getCurrentTime() / 1000;
	if (isPaused()){
		currentTime = (pauser.getReferenceTime() - timer.getReferenceTime()) / 1000;
	}
	if (currentTime < 60)
		sprintf_s(stringBuffer, "Time: %is", currentTime);
	else if (currentTime >= 60 && currentTime < 3600)
		sprintf_s(stringBuffer, "Time: %im %is", currentTime / 60, currentTime % 60);
	else
		sprintf_s(stringBuffer, "Time: %ih %im %is", currentTime / 3600, (currentTime % 3600) / 60, (currentTime % 3600) % 60);
	text.setPosition(BLOCK_GRID_WIDTH + 5, HEIGHT / 2 + 3 * FONT_SIZE);
	text.setString(stringBuffer);
	mainWindow.draw(text);


	sprintf_s(stringBuffer, "Drop Speed: %ims", getTimeDelay());
	text.setPosition(BLOCK_GRID_WIDTH + 5, HEIGHT / 2 + 4 * FONT_SIZE);
	text.setString(stringBuffer);
	mainWindow.draw(text);

	currentTime = getTimeDelay() - delayer.getCurrentTime();
	if (isPaused()){
		currentTime = pauser.getReferenceTime() - delayer.getReferenceTime();
	}
	sprintf_s(stringBuffer, "Drops in: %ims", currentTime);
	text.setPosition(BLOCK_GRID_WIDTH + 5, HEIGHT / 2 + 5 * FONT_SIZE);
	text.setString(stringBuffer);
	mainWindow.draw(text);
	
	for (int i = 0; i < blockOverlay.getBlockCount(); i++){
		mainWindow.draw(blockOverlay.getBlock(i).asRectangleShape());
	}
}

void TetrisInterface::display(){
	mainWindow.display();
}

//Resets the calling instance's members
void TetrisInterface::clear(){
	score = 0;
	linesCleared = 0;
	level = 1;
	playing = true;
	blockOverlay.clear();
	delayer.setReferenceTime(GetTickCount());
	timer.setReferenceTime(GetTickCount());
}

//Returns whether the TetrisInterface instance is still playing
bool TetrisInterface::stillPlaying(){
	return playing && mainWindow.isOpen();
}

//Sets whether the TetrisInterface instance is still playing
void TetrisInterface::setPlaying(bool playState){
	playing = playState;
}

//Returns whether the game is over for the TetrisInterface instance
bool TetrisInterface::isGameOver(){
	return gameOver;
}

//Sets whether the game is over for the TetrisInterface instance
void TetrisInterface::setGameOver(bool isGameOver){
	gameOver = isGameOver;
}

//Returns the time delay in milliseconds
int TetrisInterface::getTimeDelay(){
	if (level < 10){
		return ((19 - level)*BASE_TIME_DELAY) / 18;
	} else {
		return BASE_TIME_DELAY / 2;
	}
}

//Returns whether it is time to move the current tetrimino down based on the delayer Timer
bool TetrisInterface::isTimeToMove(){
	return delayer.timeHasPassed(getTimeDelay());
}

//Resets the delayer's reference time based on whether or not the last tetrimino downward 
//movement was forced(it was not time to move according to the delayer)
void TetrisInterface::resetDelayer(){
	if (isTimeToMove()){
		delayer.setReferenceTime(delayer.getReferenceTime() + getTimeDelay());
	} else {
		delayer.setReferenceTime(GetTickCount());
	}
}

//Returns whether the TetrisInterface instance is paused
bool TetrisInterface::isPaused(){
	return paused;
}

//Sets the pause boolean, delayer and timer reference times are adjusted when unpausing
void TetrisInterface::setPause(bool pause){
	paused = pause;
	if (!paused){
		delayer.setReferenceTime(delayer.getReferenceTime() + pauser.getCurrentTime());
		timer.setReferenceTime(timer.getReferenceTime() + pauser.getCurrentTime());
	} else {
		pauser.setReferenceTime(GetTickCount());
	}

}

//Draws a tetrimino in the side display panel
void TetrisInterface::draw(Tetrimino* current, Tetrimino* typeSource){
	draw();
	Tetrimino* tempTetrimino = typeSource->clone();
	tempTetrimino->setY(BLOCK_LENGTH);
	switch (tempTetrimino->getType()){
	case I_TETRIMINO:
		tempTetrimino->setX(BLOCK_GRID_WIDTH + (WIDTH - BLOCK_GRID_WIDTH) / 2 - BLOCK_LENGTH / 2);
		break;
	case J_TETRIMINO:
		tempTetrimino->setX(BLOCK_GRID_WIDTH + (WIDTH - BLOCK_GRID_WIDTH) / 2);
		break;
	case L_TETRIMINO:
		tempTetrimino->setX(BLOCK_GRID_WIDTH + (WIDTH - BLOCK_GRID_WIDTH) / 2 - BLOCK_LENGTH);
		break;
	case O_TETRIMINO:
		tempTetrimino->setX(BLOCK_GRID_WIDTH + (WIDTH - BLOCK_GRID_WIDTH) / 2);
		break;
	case S_TETRIMINO:
		tempTetrimino->setX(BLOCK_GRID_WIDTH + (WIDTH - BLOCK_GRID_WIDTH) / 2 + BLOCK_LENGTH / 2);
		break;
	case T_TETRIMINO:
		tempTetrimino->setX(BLOCK_GRID_WIDTH + (WIDTH - BLOCK_GRID_WIDTH) / 2 - BLOCK_LENGTH / 2);
		break;
	case Z_TETRIMINO:
		tempTetrimino->setX(BLOCK_GRID_WIDTH + (WIDTH - BLOCK_GRID_WIDTH) / 2 - 3 * BLOCK_LENGTH / 2);
		break;
	default:
		break;
	}
	for (int i = 0; i < tempTetrimino->getBlockCount(); i++){
		sf::RectangleShape block = tempTetrimino->getBlock(i).asRectangleShape();
		mainWindow.draw(block);
	}
	delete tempTetrimino;
	for (int i = 0; i < current->getBlockCount(); i++){
		sf::RectangleShape block = current->getBlock(i).asRectangleShape();
		mainWindow.draw(block);
	}
}

//Draws "Game Over" at the center of the play area, using winbgim
void TetrisInterface::drawGameOver(){
	sf::Font font;
	font.loadFromFile("resources/arial.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(2*FONT_SIZE);
	text.setFillColor(FONT_COLOR);
	text.setString("Game Over");
	text.setPosition((BLOCK_GRID_WIDTH - text.getLocalBounds().width) / 2, HEIGHT / 2);

	sf::RectangleShape back;
	back.setSize(sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height) + sf::Vector2f(4*FONT_SIZE, 4*FONT_SIZE));
	back.setFillColor(INTERFACE_OUTLINE_COLOR);
	back.setOrigin(sf::Vector2f(0, 0));
	back.setOutlineColor(FONT_COLOR);
	back.setOutlineThickness(FONT_SIZE);
	back.setPosition(text.getPosition() - sf::Vector2f(2*FONT_SIZE, 1*FONT_SIZE));
	mainWindow.draw(back);
	mainWindow.draw(text);
}

//Draws "Paused" at the center of the play area, using winbgim
void TetrisInterface::drawPaused(){
	sf::Font font;
	font.loadFromFile("resources/arial.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(2 * FONT_SIZE);
	text.setFillColor(FONT_COLOR);
	text.setString("Paused");
	text.setPosition((WIDTH - text.getLocalBounds().width) / 2, HEIGHT / 2);

	sf::RectangleShape back;
	back.setSize(sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height) + sf::Vector2f(4 * FONT_SIZE, 4 * FONT_SIZE));
	back.setFillColor(INTERFACE_OUTLINE_COLOR);
	back.setOrigin(sf::Vector2f(0, 0));
	back.setOutlineColor(FONT_COLOR);
	back.setOutlineThickness(FONT_SIZE);
	back.setPosition(text.getPosition() - sf::Vector2f(2 * FONT_SIZE, 1 * FONT_SIZE));
	mainWindow.draw(back);
	mainWindow.draw(text);
}

//Returns true only when not paused and the tetrimino can rotate, according to the BlockOverlay instance
bool TetrisInterface::tetriminoCanRotate(Tetrimino* current){
	return blockOverlay.tetriminoCanRotate(current) && !isPaused();
}

//Returns true only when not paused and the tetrimino can move left, according to the BlockOverlay instance
bool TetrisInterface::tetriminoCanMoveLeft(Tetrimino* current){
	return blockOverlay.tetriminoCanMoveLeft(current) && !isPaused();
}

//Returns true only when not paused and the tetrimino can move right, according to the BlockOverlay instance
bool TetrisInterface::tetriminoCanMoveRight(Tetrimino* current){
	return blockOverlay.tetriminoCanMoveRight(current) && !isPaused();
}

//Returns true only when not paused and the tetrimino can move down, according to the BlockOverlay instance
bool TetrisInterface::tetriminoCanMoveDown(Tetrimino* current){
	return blockOverlay.tetriminoCanMoveDown(current) && !isPaused();
}

//Returns true when a tetrimino overlays the blocks in the BlockOverlay instance
bool TetrisInterface::tetriminoOverlapsBlocks(Tetrimino* current){
	return blockOverlay.checkForOverlap(current);
}

//Adds blocks to the BlockOverlay instance through a Tetrimino instance
void TetrisInterface::addTetrimino(Tetrimino* current){
	blockOverlay.addTetriminoBlocks(current);
}

//Uses a for-loop to clear the lines in the BlockOverlay instance until no more lines are present
void TetrisInterface::clearLines(){
	for (int i = 0; blockOverlay.linesPresent(); i++){
		blockOverlay.clearLowestLine();
		addToScore((i*i + 1)*BASE_LINE_CLEAR_SCORE);
		addToLinesCleared(1);
	}
}

//Adds an integer value to the score
void TetrisInterface::addToScore(int addition){
	score += addition;
}

//Adds an integer value to the number of lines cleared and adjusts the level
void TetrisInterface::addToLinesCleared(int addition){
	linesCleared += addition;
	level = roundl(1 + linesCleared / 10);
}

//Returns the score
int TetrisInterface::getScore(){
	return score;
}

//Returns the lines cleared
int TetrisInterface::getLinesCleared(){
	return linesCleared;
}

//Returns thte level
int TetrisInterface::getLevel(){
	return level;
}

//Sets the score to an integer value
void TetrisInterface::setScore(int newScore){
	score = newScore;
}

//Sets the lines cleared to an integer value
void TetrisInterface::setLinesCleared(int newClear){
	linesCleared = newClear;
}

//Sets the level to an integer value
void TetrisInterface::setLevel(int newLevel){
	level = newLevel;
}


bool TetrisInterface::pollEvent(){
	bool returnValue = mainWindow.pollEvent(currentEvent);
		if ((currentEvent.type == sf::Event::Closed) || 
			((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Escape))){
			mainWindow.close();
			playing = false;
		}
		return returnValue && currentEvent.type == sf::Event::KeyPressed;

}

sf::Keyboard::Key TetrisInterface::getEventKey(){
	return currentEvent.key.code;
}

void TetrisInterface::clearDisplay(){
	mainWindow.clear(BACKGROUND_COLOR);
}