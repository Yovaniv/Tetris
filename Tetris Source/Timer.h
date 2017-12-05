/*
	Timer.h
	Declares the Timer class prototype.
*/

#pragma once

class Timer{
public:
	Timer();
	Timer(int startTime);
	bool timeHasPassed(int timeDelay);
	int getCurrentTime();
	int getReferenceTime();
	void setReferenceTime(int newTime);
private:
	int referenceTime;
};