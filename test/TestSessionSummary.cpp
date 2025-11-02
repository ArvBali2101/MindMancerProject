#include <iostream>

#include "../include/SessionSummary.h"

int main() {
  SessionSummary summary("test_log.txt");
  summary.readLogFile();
  summary.display();
  summary.showTaskDurations();
  summary.showTotalTimeSpent();

  std::cout << "✅ TestSessionSummary completed.\n";
  return 0;
}
