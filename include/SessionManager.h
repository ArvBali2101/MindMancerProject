#pragma once  // Prevents multiple inclusion of this header

#include <chrono>
#include <iostream>
#include <string>
using namespace std;

// Forward declaration
class TaskLogger;

// Base session timer class with pause/resume/stop and logging
class SessionManager {
 protected:
  TaskLogger& myLogger;  // ✅ Logger reference
  int myDuration;
  bool myIsRunning;
  bool myIsPaused;

  chrono::steady_clock::time_point myStartTime;
  chrono::steady_clock::time_point myPauseTime;
  chrono::seconds myPausedDuration;

 public:
  // ✅ Correct constructor with logger
  SessionManager(TaskLogger& logger);
  virtual ~SessionManager();

  // Pure virtual methods for derived classes
  virtual void startTask(string taskDescription) = 0;
  virtual void stopTask() = 0;

  // Timer controls
  virtual void setSessionDuration(int timerDuration);
  void startTimer();
  void stopTimer();
  void pauseTimer();
  void resumeTimer();
  void resetTimer();

  // Status queries
  bool isTimerRunning() const;
  bool isTimerPaused() const;
  bool isTimerExpired() const;
  int getRemainingTime() const;

  // Runtime updates
  virtual void updateTimer();
  virtual void display() const;
};
