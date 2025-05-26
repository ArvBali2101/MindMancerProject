#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

#include "../include/TimerCount.h"
#include "../include/WorkSessionManager.h"

using namespace std;

// Test 1: Set and check session duration
void testSessionDuration() {
  TimerCount timerCount;
  WorkSessionManager session(timerCount);

  session.setSessionDuration(20);
  assert(session.getRemainingTime() == 20);
  cout << "✅ testSessionDuration passed.\n";
}

// Test 2: Ensure TimerCount increments after a session
void testTimerCountIncrement() {
  TimerCount timerCount;
  WorkSessionManager session(timerCount);

  int before = timerCount.getTimerCount();
  session.setSessionDuration(5);
  session.startTask("Dummy Session");

  // Simulate running the timer briefly
  this_thread::sleep_for(chrono::seconds(1));
  session.resetTimer();
  session.stopTask();

  int after = timerCount.getTimerCount();
  assert(after == before + 1);
  cout << "✅ testTimerCountIncrement passed.\n";
}

// Test 3: Pause and resume functionality
void testPauseResume() {
  TimerCount timerCount;
  WorkSessionManager session(timerCount);

  session.setSessionDuration(10);
  session.startTask("Pause Resume Test");

  session.pauseTimer();
  assert(session.isTimerPaused());
  session.resumeTimer();
  assert(!session.isTimerPaused());

  session.resetTimer();
  cout << "✅ testPauseResume passed.\n";
}

int main() {
  testSessionDuration();
  testTimerCountIncrement();
  testPauseResume();

  cout << "✅ All WorkSessionManager tests passed.\n";
  return 0;
}
