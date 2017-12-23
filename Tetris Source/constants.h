/*
	Constants and enumerations to be used by the Tetris program. 
*/

#pragma once
#include "SFML\Graphics.hpp"

const int BLOCKS_PER_GRID_WIDTH = 10;
const int BLOCKS_PER_GRID_HEIGHT = 1.5*BLOCKS_PER_GRID_WIDTH;
const int BLOCK_LENGTH = 40;
const int HEIGHT = BLOCKS_PER_GRID_HEIGHT*BLOCK_LENGTH;
const double INTERFACE_FRACTION = 0.4;
const int WIDTH = (BLOCKS_PER_GRID_WIDTH*BLOCK_LENGTH) / (1 - INTERFACE_FRACTION);
const int WINDOW_BORDER_X = 11;
const int WINDOW_BORDER_Y = 11;
const int DRAWABLE_WIDTH = WIDTH;
const int DRAWABLE_HEIGHT = HEIGHT;

const int INTERFACE_WIDTH = INTERFACE_FRACTION*DRAWABLE_WIDTH;
const int INTERFACE_HEIGHT = DRAWABLE_HEIGHT;
const sf::Color INTERFACE_COLOR = sf::Color::Blue;
const sf::Color INTERFACE_OUTLINE_COLOR = sf::Color::Black;
const int INTERFACE_OUTLINE_THICKNESS = 3;
const int SECONDS_BEFORE_DROP = 1;
const int BASE_TIME_DELAY = 1000 * SECONDS_BEFORE_DROP;
const int BASE_LINE_CLEAR_SCORE = 100;

const sf::Color BACKGROUND_COLOR = sf::Color(75, 75, 75, 255);
const int FONT_SIZE = 20;
const sf::Color FONT_COLOR = sf::Color::White;

const sf::Color DEFAULT_BLOCK_OUTLINE_COLOR = sf::Color::White;
const int BLOCK_OUTLINE_THICKNESS = BLOCK_LENGTH/15;
const sf::Color DEFAULT_BLOCK_COLOR = INTERFACE_COLOR;
const int BLOCK_GRID_WIDTH = DRAWABLE_WIDTH-INTERFACE_WIDTH;
const int BLOCK_GRID_HEIGHT = DRAWABLE_HEIGHT;
//const int BLOCKS_PER_GRID_WIDTH = 10;
//const int BLOCK_LENGTH = BLOCK_GRID_WIDTH / BLOCKS_PER_GRID_WIDTH;// -2;
//const int BLOCKS_PER_GRID_HEIGHT = HEIGHT/ BLOCK_LENGTH ;
const int GRID_BLOCKS = BLOCKS_PER_GRID_HEIGHT * BLOCKS_PER_GRID_WIDTH;

enum TetriminoType {
	I_TETRIMINO = 0, J_TETRIMINO, L_TETRIMINO, O_TETRIMINO, S_TETRIMINO, T_TETRIMINO, Z_TETRIMINO
};

enum TetriminoOrientation {
	TOP_FACING_TOP = 0, TOP_FACING_RIGHT, TOP_FACING_BOTTOM, TOP_FACING_LEFT
};

const int TETRIMINO_TYPE_COUNT = Z_TETRIMINO;
const sf::Color I_TETRIMINO_COLOR = sf::Color::Cyan;
const sf::Color J_TETRIMINO_COLOR = sf::Color::Red;
const sf::Color L_TETRIMINO_COLOR = sf::Color::Blue;
const sf::Color O_TETRIMINO_COLOR = sf::Color::Yellow;
const sf::Color S_TETRIMINO_COLOR = sf::Color::Green;
const sf::Color T_TETRIMINO_COLOR = sf::Color::Black;
const sf::Color Z_TETRIMINO_COLOR = sf::Color::Magenta;

