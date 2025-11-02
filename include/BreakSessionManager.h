#pragma once  // Prevents multiple inclusion of this header file

#include "SessionManager.h"
#include "TaskLogger.h"
#include "TimerCount.h"

// Manages a break session, typically triggered after multiple work sessions.
// Inherits from SessionManager and uses a TimerCount reference to track
// progress.
class BreakSessionManager : public SessionManager {
 private:
  TimerCount&
      myTimerCount;  // Reference to shared TimerCount to track session flow
  int mysessionDuration;  // Duration of the break session

 public:
  // Constructor: Accepts a TaskLogger and a TimerCount reference
  BreakSessionManager(TaskLogger& logger, TimerCount& myTimerCount);

  // Starts the break session with a description and logs it
  void startTask(string taskDescription) override;

  // Stops the break session and finalizes logging
  void stopTask() override;

  // Displays current break session settings
  void display() const;

  // Sets the break session duration in seconds
  void setSessionDuration(int sessionDuration);
};
