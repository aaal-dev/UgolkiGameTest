#include "time.hpp"

Time::Time(){}

Time::~Time(){}

void Time::init() {
	lastTime = clock.getElapsedTime().asMilliseconds();
}
unsigned int Time::getTime() {
	return clock.getElapsedTime().asMilliseconds();
}

unsigned int Time::getDeltaTime() {
	return getTime() - lastTime;
}