#pragma once  // Prevents multiple inclusion of this header file

#include "SessionManager.h"
#include "TimerCount.h"

// Manages a single work session by inheriting from SessionManager.
// Uses a TimerCount object to track session completions.
class WorkSessionManager : public SessionManager {
 private:
  TimerCount& myTimerCount;  // Reference to a TimerCount for tracking number of
                             // work sessions
  int mySessionDuration;     // Duration of the current work session

 public:
  // Constructor: Takes a TimerCount reference
  WorkSessionManager(TimerCount& timerCount);

  // Starts the work session and begins countdown
  void startTask(string taskDescription) override;

  // Stops the session and ends the timer
  void stopTask() override;

  // Sets the work session duration in seconds
  void setSessionDuration(int sessionDuration);

  // Displays current session details (for debugging or output)
  void display() const;
};
