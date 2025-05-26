#include "SessionManager.h"

#ifdef _WIN32
#include <conio.h>  // For Windows input
#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#endif

// Constructor: Initializes session state and timer
SessionManager::SessionManager()
    : myDuration(0),
      myIsRunning(false),
      myIsPaused(false),
      myPausedDuration(0) {}

// Destructor: No dynamic memory, nothing to clean up
SessionManager::~SessionManager() {}

// Sets the session duration in seconds
void SessionManager::setSessionDuration(int timerDuration) {
  myDuration = timerDuration;
}

// Starts or restarts the timer with reset pause state
void SessionManager::startTimer() {
  myIsRunning = true;
  myIsPaused = false;
  myPausedDuration = chrono::seconds(0);
  myStartTime = chrono::steady_clock::now();

  cout << "Press 'p' to pause, 'r' to resume, 'q' to quit.\n";
}

// Stops the timer without resetting the state
void SessionManager::stopTimer() { myIsRunning = false; }

// Pauses the timer and logs the pause event
void SessionManager::pauseTimer() {
  if (myIsRunning && !myIsPaused) {
    myIsPaused = true;
    myPauseTime = chrono::steady_clock::now();
    cout << "\nPaused.\n";
  }
}

// Resumes the timer and adjusts paused duration
void SessionManager::resumeTimer() {
  if (myIsRunning && myIsPaused) {
    auto now = chrono::steady_clock::now();
    myPausedDuration +=
        chrono::duration_cast<chrono::seconds>(now - myPauseTime);
    myIsPaused = false;
    cout << "\nResumed.\n";
  }
}

// Resets the timer state and logs the reset
void SessionManager::resetTimer() {
  myIsRunning = false;
  myIsPaused = false;
  myPausedDuration = chrono::seconds(0);
  cout << "\nTimer stopped.\n";
}

// Returns true if the timer is active and not yet expired
bool SessionManager::isTimerRunning() const {
  return myIsRunning && !isTimerExpired();
}

// Returns true if the timer has reached the session duration
bool SessionManager::isTimerExpired() const {
  if (!myIsRunning || myIsPaused) return false;

  auto now = chrono::steady_clock::now();
  auto elapsed = chrono::duration_cast<chrono::seconds>(now - myStartTime -
                                                        myPausedDuration);
  return elapsed.count() >= myDuration;
}

// Returns how many seconds are left in the session
int SessionManager::getRemainingTime() const {
  if (!myIsRunning) return myDuration;

  auto now = myIsPaused ? myPauseTime : chrono::steady_clock::now();
  auto elapsed = chrono::duration_cast<chrono::seconds>(now - myStartTime -
                                                        myPausedDuration);

  int remaining = myDuration - static_cast<int>(elapsed.count());
  return remaining > 0 ? remaining : 0;
}

// Updates the timer state, checks for input and prints countdown
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
  // Linux/macOS input detection without Enter
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

  // Display remaining time if running and not paused or expired
  if (myIsRunning && !myIsPaused && !isTimerExpired()) {
    cout << "\rTime left: " << getRemainingTime() << "s   " << flush;
  }

  // Handle session completion
  if (myIsRunning && isTimerExpired()) {
    cout << "\n[Timer finished]\n";
    myIsRunning = false;
  }
}

// Displays the current timer status in console
void SessionManager::display() const {
  cout << "Session Duration: " << myDuration << " seconds\n";
  cout << "Timer is " << (myIsRunning ? "running" : "not running") << endl;
  cout << "Timer is " << (myIsPaused ? "paused" : "not paused") << endl;
}
