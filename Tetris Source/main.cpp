/*
	main.cpp
	Uses winbgim to display a Tetris game, where sets of blocks known as tetriminos 
	are continually stacked on top of each other. When a horizontal line of blocks is 
	formed, it is cleared therby increasing the score, level, and difficulty. When a tetrimino cannot be added to 
	the play area due to the existing blocks being too high, the current game is over.
*/

#include "TetrisInterface.h"
#include "RandomTetrimino.h"

//The main program loop, which primarily handles the current tetrimino and interface interactions
int main(){
	bool page = false, forcedTetriminoToMoveDown = false;
	srand(GetTickCount());
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
			setactivepage(page);
			setbkcolor(BACKGROUND_COLOR);

			tetrisInterface.draw(queuedTetrimino);
			currentTetrimino->draw();

			if (tetrisInterface.isGameOver()){
				tetrisInterface.drawGameOver();
			} else if (tetrisInterface.isPaused()){
				tetrisInterface.drawPaused();
			}
			setvisualpage(page);

			if (kbhit() && !tetrisInterface.isGameOver()){
				switch (getch()){
				case KEY_UP:
				case 'w':
				case 'W':
					if (tetrisInterface.tetriminoCanRotate(currentTetrimino)){
						currentTetrimino->rotate();
					}
					break;
				case KEY_LEFT:
				case 'a':
				case 'A':
					if (tetrisInterface.tetriminoCanMoveLeft(currentTetrimino)){
						currentTetrimino->moveLeft();
					}
					break;
				case KEY_RIGHT:
				case 'd':
				case 'D':
					if (tetrisInterface.tetriminoCanMoveRight(currentTetrimino)){
						currentTetrimino->moveRight();
					}
					break;
				case KEY_DOWN:
				case 's':
				case 'S':
					if (tetrisInterface.tetriminoCanMoveDown(currentTetrimino)){
						currentTetrimino->moveDown();
					} else {
						forcedTetriminoToMoveDown = true;
					}
					break;
				case KEY_SPACE:
				case KEY_ENTER:
					while (tetrisInterface.tetriminoCanMoveDown(currentTetrimino)){
						currentTetrimino->moveDown();
					}
					forcedTetriminoToMoveDown = true;
					break;
				case 'p':
					if (tetrisInterface.isPaused()){
						tetrisInterface.setPause(false);
					} else {
						tetrisInterface.setPause(true);
					}
					break;
				case KEY_ESC:
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
			setvisualpage(page);
			page = !page;
			setactivepage(page);
			delay(35);
			cleardevice();
		} else {
			switch (getch()){
			case KEY_SPACE:
			case KEY_ENTER:
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
			case KEY_ESC:
				tetrisInterface.setPlaying(false);
				break;
			default:
				break;
			}
			delay(35);
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