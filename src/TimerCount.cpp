#include "TimerCount.h"

// Constructor: Initializes the counter to zero
TimerCount::TimerCount() : myCount(0) {}

// Increments the session counter by one
void TimerCount::incrementTimerCount() { myCount++; }

// Returns the current count of completed sessions
int TimerCount::getTimerCount() { return myCount; }

// reset the current session count
void TimerCount::resetTimerCount() { myCount = 0; }

// Displays the current session count in the console
void TimerCount::display() const { cout << "Timer Count: " << myCount << endl; }