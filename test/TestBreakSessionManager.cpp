#include <cassert>
#include <iostream>

#include "../include/BreakSessionManager.h"
#include "../include/TaskLogger.h"
#include "../include/TimerCount.h"

int main() {
  TimerCount timerCount;
  TaskLogger logger;
  logger.setLogFileName("test_log.txt");

  BreakSessionManager session(logger, timerCount);

  session.setSessionDuration(5);  // base duration
  session.startTask("Test Break");

  assert(session.isTimerRunning());
  session.stopTask();

  std::cout << "✅ TestBreakSessionManager passed.\n";
  return 0;
}
