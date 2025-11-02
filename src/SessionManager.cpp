#include "SessionManager.h"

#include "TaskLogger.h"

#ifndef _WIN32
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#else
#include <conio.h>
#endif

SessionManager::SessionManager(TaskLogger& logger)
    : myLogger(logger),
      myDuration(0),
      myIsRunning(false),
      myIsPaused(false),
      myPausedDuration(0) {}

SessionManager::~SessionManager() {}

void SessionManager::setSessionDuration(int timerDuration) {
  myDuration = timerDuration;
}

void SessionManager::startTimer() {
  myIsRunning = true;
  myIsPaused = false;
  myPausedDuration = chrono::seconds(0);
  myStartTime = chrono::steady_clock::now();
  cout << "Press 'p' to pause, 'r' to resume, 'q' to quit.\n";
}

void SessionManager::stopTimer() { myIsRunning = false; }

void SessionManager::pauseTimer() {
  if (myIsRunning && !myIsPaused) {
    myIsPaused = true;
    myPauseTime = chrono::steady_clock::now();
    cout << "\nPaused.\n";
    myLogger.logTask("Paused");
  }
}

void SessionManager::resumeTimer() {
  if (myIsRunning && myIsPaused) {
    auto now = chrono::steady_clock::now();
    myPausedDuration +=
        chrono::duration_cast<chrono::seconds>(now - myPauseTime);
    myIsPaused = false;
    cout << "\nResumed.\n";
    myLogger.logTask("Resumed");
  }
}

void SessionManager::resetTimer() {
  myIsRunning = false;
  myIsPaused = false;
  myPausedDuration = chrono::seconds(0);
  cout << "\nTimer stopped.\n";
  myLogger.logTask("Timer stopped");
}

bool SessionManager::isTimerRunning() const {
  return myIsRunning && !isTimerExpired();
}

bool SessionManager::isTimerPaused() const { return myIsPaused; }

bool SessionManager::isTimerExpired() const {
  if (!myIsRunning || myIsPaused) return false;
  auto now = chrono::steady_clock::now();
  auto elapsed = chrono::duration_cast<chrono::seconds>(now - myStartTime -
                                                        myPausedDuration);
  return elapsed.count() >= myDuration;
}

int SessionManager::getRemainingTime() const {
  if (!myIsRunning) return myDuration;
  auto now = myIsPaused ? myPauseTime : chrono::steady_clock::now();
  auto elapsed = chrono::duration_cast<chrono::seconds>(now - myStartTime -
                                                        myPausedDuration);
  int remaining = myDuration - static_cast<int>(elapsed.count());
  return remaining > 0 ? remaining : 0;
}

void SessionManager::updateTimer() {
#ifdef _WIN32
  if (_kbhit()) {
    char ch = _getch();
    if (ch == 'p')
      pauseTimer();
    else if (ch == 'r')
      resumeTimer();
    else if (ch == 'q')
      resetTimer();
  }
#else
  struct termios oldt, newt;
  int oldf;
  char ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  if (read(STDIN_FILENO, &ch, 1) > 0) {
    if (ch == 'p')
      pauseTimer();
    else if (ch == 'r')
      resumeTimer();
    else if (ch == 'q')
      resetTimer();
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
#endif

  if (myIsRunning && !myIsPaused && !isTimerExpired()) {
    cout << "\rTime left: " << getRemainingTime() << "s   " << flush;
  }

  if (myIsRunning && isTimerExpired()) {
    cout << "\n[Timer finished]\n";
    myLogger.logTask("Timer finished");
    myIsRunning = false;
  }
}

void SessionManager::display() const {
  cout << "Session Duration: " << myDuration << " seconds\n";
  cout << "Timer is " << (myIsRunning ? "running" : "not running") << endl;
  cout << "Timer is " << (myIsPaused ? "paused" : "not paused") << endl;
}
