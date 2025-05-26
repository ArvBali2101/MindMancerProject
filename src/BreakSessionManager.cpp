#include "BreakSessionManager.h"

// Constructor: Initializes the base SessionManager and stores TimerCount
// reference
BreakSessionManager::BreakSessionManager(TaskLogger& logger,
                                         TimerCount& timerCount)
    : SessionManager(logger), myTimerCount(timerCount), mysessionDuration(0) {}

// Starts the break session and begins logging and countdown
void BreakSessionManager::startTask(string taskDescription) {
  myLogger.startLogging(taskDescription);
  startTimer();
}

// Sets the break duration based on number of completed work sessions
// Every 4th session triggers a long break (3x duration)
void BreakSessionManager::setSessionDuration(int sessionDuration) {
  cout << myTimerCount.getTimerCount() << endl;
  mysessionDuration = sessionDuration;

  if ((myTimerCount.getTimerCount() != 0) &&
      ((myTimerCount.getTimerCount() % 4) == 0)) {
    cout << "\nLong Break of " << mysessionDuration * 3
         << " seconds started...." << endl;
    SessionManager::setSessionDuration(mysessionDuration * 3);
  } else {
    cout << "\nShort Break of " << mysessionDuration << " seconds started...."
         << endl;
    SessionManager::setSessionDuration(mysessionDuration);
  }
}

// Stops the current break session and finalizes logging
void BreakSessionManager::stopTask() {
  myLogger.stopLogging();
  stopTimer();
}

// Displays the configured break session duration
void BreakSessionManager::display() const {
  cout << "Break Session of " << mysessionDuration << " seconds started"
       << endl;
}
