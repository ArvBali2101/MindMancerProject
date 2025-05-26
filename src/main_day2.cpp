#include <chrono>
#include <iostream>
#include <thread>

#include "TimerCount.h"
#include "WorkSessionManager.h"

using namespace std;

int main() {
  // Create a TimerCount object to track how many sessions have occurred
  TimerCount myTimerCount;

  // Create a WorkSessionManager with the TimerCount (no logger needed)
  WorkSessionManager workSession(myTimerCount);

  while (true) {
    cout << "\n==== MindMancer – Day 2 ====\n";
    cout << "1. Start Work Session\n";
    cout << "2. View Session Count\n";
    cout << "3. Exit\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
      // Set a short test session
      workSession.setSessionDuration(10);  // 10 seconds

      // Start a work session with a description
      workSession.startTask("Work Session");

      // While the timer is running, keep updating
      while (workSession.isTimerRunning()) {
        workSession.updateTimer();
        this_thread::sleep_for(chrono::milliseconds(500));
      }

      // Stop the session
      workSession.stopTask();
    } else if (choice == 2) {
      // Show how many sessions have been completed
      myTimerCount.display();
    } else if (choice == 3) {
      cout << "Exiting... Stay focused!\n";
      break;
    } else {
      cout << "Invalid input. Try again.\n";
    }
  }

  return 0;
}
