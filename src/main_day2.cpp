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

  int choice;

  while (true) {
    cout << "\n==== MindMancer – Day 2 ====\n";
    cout << "1. Start Work Session\n";
    cout << "2. View Session Count\n";
    cout << "3. Exit\n";
    cout << "Choice: ";

    cin.clear();             // ✅ Clear any previous error
    cin.ignore(1000, '\n');  // ✅ Remove leftover keystrokes from input buffer
    cin >> choice;

    if (choice == 1) {
      // Set a short test session
      workSession.setSessionDuration(10);  // 10 seconds

      // Start a work session with a description
      workSession.startTask("Work Session");

      // While the timer is running, keep updating
      while (true) {
        workSession.updateTimer();

        // ✅ Break when timer ends or user presses 'q'
        if (!workSession.isTimerRunning()) break;

        this_thread::sleep_for(chrono::milliseconds(500));
      }

      // Stop the session explicitly
      workSession.stopTask();

      // ✅ Final fix: clean any leftover characters in the buffer
      cin.clear();
      while (cin.peek() != '\n' && cin.peek() != EOF) {
        cin.get();
      }
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
