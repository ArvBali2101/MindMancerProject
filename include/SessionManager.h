#pragma once  // Prevents multiple inclusion of this header during compilation

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#ifdef _WIN32
#include <conio.h>  // For _kbhit() and _getch() input detection (Windows only)
#endif
using namespace std;

// Base class for session timers (e.g., WorkSession, BreakSession)
class SessionManager {
 protected:
  int myDuration;            // Total session duration in seconds
  atomic<bool> myIsRunning;  // True if the timer is currently active
  atomic<bool> myIsPaused;   // True if the timer is paused

  // Time points for tracking start and pause moments
  chrono::steady_clock::time_point myStartTime;
  chrono::steady_clock::time_point myPauseTime;

  // Total time spent in paused state
  chrono::seconds myPausedDuration;

 public:
  SessionManager();           // Constructor
  virtual ~SessionManager();  // Destructor

  void setSessionDuration(int timerDuration);  // Sets duration
  void startTimer();                           // Starts countdown
  void stopTimer();                            // Stops session
  void pauseTimer();                           // Pause timer
  void resumeTimer();                          // Resume timer
  void resetTimer();                           // Reset session

  bool isTimerRunning() const;
  bool isTimerPaused() const;
  bool isTimerExpired() const;
  int getRemainingTime() const;

  virtual void updateTimer();    // Updates time / input
  virtual void display() const;  // Print status
  virtual void startTask(string taskDescription) = 0;
  virtual void stopTask() = 0;
};
