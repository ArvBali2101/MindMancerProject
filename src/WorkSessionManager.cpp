#include "WorkSessionManager.h"

// Constructor: Initializes base SessionManager and stores reference to
// TimerCount
WorkSessionManager::WorkSessionManager(TaskLogger& logger,
                                       TimerCount& timerCount)
    : SessionManager(logger), myTimerCount(timerCount) {}

// Starts a new work session with the given description
void WorkSessionManager::startTask(string taskDescription) {
  cout << "\nWork Session of " << mySessionDuration << " seconds started"
       << endl;

  myLogger.startLogging(taskDescription);
  myTimerCount.incrementTimerCount();
  startTimer();
}

// Sets the session duration and applies it to the base class
void WorkSessionManager::setSessionDuration(int sessionDuration) {
  mySessionDuration = sessionDuration;
  SessionManager::setSessionDuration(mySessionDuration);
}

// Stops the session timer and ends the log entry
void WorkSessionManager::stopTask() {
  myLogger.stopLogging();
  stopTimer();
}

// Displays the current session duration
void WorkSessionManager::display() const {
  cout << "Work Session duration: " << mySessionDuration << " seconds" << endl;
}
