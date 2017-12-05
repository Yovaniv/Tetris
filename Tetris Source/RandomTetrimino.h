/*
	RandomTetrimimno.h
	Declares the random generation functions of the Tetris program.
*/

#pragma once
#include "Tetriminos.h"
#include "constants.h"

//Returns a random integer between min and max using rand
//Note: The rand function needs to be preseeded with srand
int random(int min, int max){
	return rand() % (max + 1) + min;
}

//Returns a random integer between zero and max
//Note: The rand function needs to be preseeded with srand
int random(int max){
	return random(0, max);
}

//Returns a pointer to a derived Tetrimino Class
Tetrimino* randomTetrimino(){
	switch (random(TETRIMINO_TYPE_COUNT)){
	case I_TETRIMINO:
		return new ITetrimino();
		break;
	case J_TETRIMINO:
		return new JTetrimino();
		break;
	case L_TETRIMINO:
		return new LTetrimino();
		break;
	case O_TETRIMINO:
		return new OTetrimino();
		break;
	case S_TETRIMINO:
		return new STetrimino();
		break;
	case T_TETRIMINO:
		return new TTetrimino();
		break;
	case Z_TETRIMINO:
		return new ZTetrimino();
		break;
	default:
		return new ITetrimino();
	}
};