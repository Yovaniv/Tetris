/*
	Timer.cpp
	Defines the methods and members of the Timer class.
*/

#include "timer.h"
#include <Windows.h>

//Default Timer constructor that automatically sets the reference time as the time since system start up
Timer::Timer(){
	referenceTime = GetTickCount();
}

//Timer constructor that sets a specific reference time
Timer::Timer(int startTime){
	referenceTime = startTime;
}

//Returns whether the a number of milliseconds have passed since the reference time
bool Timer::timeHasPassed(int timeDelay){
	return (getCurrentTime() >= timeDelay);
}

//Returns the time that has passed since the reference time in milliseconds
int Timer::getCurrentTime(){
	return (GetTickCount()-referenceTime);
}

//Sets the reference time, should be used with GetTickCount
int Timer::getReferenceTime(){
	return referenceTime;
}

void Timer::setReferenceTime(int newTime){
	referenceTime = newTime;
}