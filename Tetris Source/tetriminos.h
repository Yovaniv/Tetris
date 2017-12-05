/*
	Tetrimino.h
	Declares the ITetrimino, JTetrimino, LTetrimino, OTetrimino, STetrimino, 
	TTetrimino, ZTetrimino class prototypes. These are classes derived from 
	the Tetrimino class.
*/

#pragma once
#include "Tetrimino.h"

class ITetrimino : public Tetrimino{
public:
	ITetrimino();
	~ITetrimino();
	void rotate();
	Tetrimino* clone();
	virtual void setX(int newX);
	virtual void setY(int setY);
};

class JTetrimino : public Tetrimino{
public:
	JTetrimino();
	~JTetrimino();
	void rotate();
	Tetrimino* clone();
	virtual void setX(int newX);
	virtual void setY(int setY);
};

class LTetrimino : public Tetrimino{
public:
	LTetrimino();
	~LTetrimino();
	void rotate();
	Tetrimino* clone();
	virtual void setX(int newX);
	virtual void setY(int setY);
};

class OTetrimino : public Tetrimino{
public:
	OTetrimino();
	~OTetrimino();
	void rotate();
	Tetrimino* clone();
	virtual void setX(int newX);
	virtual void setY(int setY);
};

class STetrimino : public Tetrimino{
public:
	STetrimino();
	~STetrimino();
	void rotate();
	Tetrimino* clone();
	virtual void setX(int newX);
	virtual void setY(int setY);
};

class TTetrimino : public Tetrimino{
public:
	TTetrimino();
	~TTetrimino();
	void rotate();
	Tetrimino* clone();
	virtual void setX(int newX);
	virtual void setY(int setY);
};

class ZTetrimino : public Tetrimino{
public:
	ZTetrimino();
	~ZTetrimino();
	void rotate();
	Tetrimino* clone();
	virtual void setX(int newX);
	virtual void setY(int setY);
};