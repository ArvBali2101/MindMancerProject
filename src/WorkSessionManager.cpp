#include "WorkSessionManager.h"

// Constructor: Initializes base SessionManager and stores reference to
// TimerCount
WorkSessionManager::WorkSessionManager(TimerCount& timerCount)
    : SessionManager(), myTimerCount(timerCount) {}

// Starts a new work session with the given description
// Increments the timer count and starts the countdown
void WorkSessionManager::startTask(string taskDescription) {
  cout << "Work Session of " << mySessionDuration << " seconds started" << endl;

  // Count this session in the timer tracker
  myTimerCount.incrementTimerCount();

  // Begin the timer countdown
  startTimer();
}

// Sets the session duration and applies it to the base class
void WorkSessionManager::setSessionDuration(int sessionDuration) {
  mySessionDuration = sessionDuration;

  // Forward duration setting to base SessionManager
  SessionManager::setSessionDuration(mySessionDuration);
}

// Stops the session timer
void WorkSessionManager::stopTask() { stopTimer(); }

// Displays the current session duration
void WorkSessionManager::display() const {
  cout << "Work Session duration: " << mySessionDuration << " seconds" << endl;
}
