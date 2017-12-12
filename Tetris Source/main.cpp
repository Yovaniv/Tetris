/*
	main.cpp
	Uses SFML to display a Tetris game, where sets of blocks known as tetriminos 
	are continually stacked on top of each other. When a horizontal line of blocks is 
	formed, it is cleared therby increasing the score, level, and difficulty. When a tetrimino cannot be added to 
	the play area due to the existing blocks being too high, the current game is over.
*/

#include "TetrisInterface.h"
#include "RandomTetrimino.h"
#include "SFML\Graphics.hpp"

//The main program loop, which primarily handles the current tetrimino and interface interactions
int main(){
	bool page = false, forcedTetriminoToMoveDown = false;
	std::srand(GetTickCount());
	Tetrimino* currentTetrimino = nullptr;
	Tetrimino* queuedTetrimino = randomTetrimino();
	TetrisInterface tetrisInterface = TetrisInterface();

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	while (tetrisInterface.stillPlaying()){
		if (!tetrisInterface.isGameOver()){
			if (currentTetrimino == nullptr){
				currentTetrimino = queuedTetrimino;
				queuedTetrimino = randomTetrimino();
				if (tetrisInterface.tetriminoOverlapsBlocks(currentTetrimino)){
					tetrisInterface.setGameOver(true);
				}
			}

			tetrisInterface.draw(currentTetrimino, queuedTetrimino);
			if (tetrisInterface.isGameOver()){
				tetrisInterface.drawGameOver();
			} else if (tetrisInterface.isPaused()){
				tetrisInterface.drawPaused();
			}
			tetrisInterface.display();

			if (tetrisInterface.pollEvent() && !tetrisInterface.isGameOver()){
				switch (tetrisInterface.getEventKey()){
				case sf::Keyboard::Up:
				case sf::Keyboard::W:
					if (tetrisInterface.tetriminoCanRotate(currentTetrimino)){
						currentTetrimino->rotate();
					}
					break;
				case sf::Keyboard::Left:
				case sf::Keyboard::A:
					if (tetrisInterface.tetriminoCanMoveLeft(currentTetrimino)){
						currentTetrimino->moveLeft();
					}
					break;
				case sf::Keyboard::Right:
				case sf::Keyboard::D:
					if (tetrisInterface.tetriminoCanMoveRight(currentTetrimino)){
						currentTetrimino->moveRight();
					}
					break;
				case sf::Keyboard::Down:
				case sf::Keyboard::S:
					if (tetrisInterface.tetriminoCanMoveDown(currentTetrimino)){
						currentTetrimino->moveDown();
					} else {
						forcedTetriminoToMoveDown = true;
					}
					break;
				case sf::Keyboard::Space:
				case sf::Keyboard::Return:
					while (tetrisInterface.tetriminoCanMoveDown(currentTetrimino)){
						currentTetrimino->moveDown();
					}
					forcedTetriminoToMoveDown = true;
					break;
				case sf::Keyboard::P:
					if (tetrisInterface.isPaused()){
						tetrisInterface.setPause(false);
					} else {
						tetrisInterface.setPause(true);
					}
					break;
				case sf::Keyboard::Escape:
					tetrisInterface.setPlaying(false);
					break;
				default:
					break;
				}
			}
			if ((tetrisInterface.isTimeToMove() || forcedTetriminoToMoveDown) && !tetrisInterface.isGameOver() && !tetrisInterface.isPaused()){
				forcedTetriminoToMoveDown = false;
				tetrisInterface.resetDelayer();
				if (tetrisInterface.tetriminoCanMoveDown(currentTetrimino)){
					currentTetrimino->moveDown();
				} else {
					if (tetrisInterface.tetriminoOverlapsBlocks(currentTetrimino)){
						tetrisInterface.setGameOver(true);
						tetrisInterface.drawGameOver();
					} else {
						tetrisInterface.addTetrimino(currentTetrimino);
						delete currentTetrimino;
						currentTetrimino = nullptr;
					}
				}
				tetrisInterface.clearLines();
			}
			tetrisInterface.clearDisplay();
		} else {
			if (tetrisInterface.pollEvent()){
				switch (tetrisInterface.getEventKey()){
				case sf::Keyboard::Space:
				case sf::Keyboard::Return:
					tetrisInterface.clear();
					if (currentTetrimino != nullptr){
						delete currentTetrimino;
						currentTetrimino = nullptr;
					}
					if (queuedTetrimino != nullptr){
						delete queuedTetrimino;
						queuedTetrimino = nullptr;
					}
					queuedTetrimino = randomTetrimino();
					tetrisInterface.setGameOver(false);
					break;
				case sf::Keyboard::Escape:
					tetrisInterface.setPlaying(false);
					break;
				default:
					break;
				}
			}
			//delay(35);
		}
	}
	if (currentTetrimino != nullptr){
		delete currentTetrimino;
	}
	if (queuedTetrimino != nullptr){
		delete queuedTetrimino;
	}
	return 0;
}