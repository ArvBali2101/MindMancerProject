#include <chrono>
#include <iostream>
#include <thread>

#include "BreakSessionManager.h"
#include "MotivationalQuoteManager.h"
#include "SessionSummary.h"
#include "TaskLogger.h"
#include "TimerCount.h"
#include "WorkSessionManager.h"

using namespace std;

int main() {
  TimerCount timerCount;
  TaskLogger logger;
  logger.setLogFileName("day3_log.txt");

  WorkSessionManager workSession(logger, timerCount);
  BreakSessionManager breakSession(logger, timerCount);
  MotivationalQuoteManager quoteManager(30);  // every 10 sec
  SessionSummary summary("day3_log.txt");

  int choice;

  while (true) {
    cout << "\n==== MindMancer – Day 3 Menu ====\n";
    cout << "1. Start Work Session\n";
    cout << "2. Start Break Session\n";
    cout << "3. Show Motivational Quote Info\n";
    cout << "4. Show Session Summary\n";
    cout << "5. Run Full Pomodoro Cycle (4x)\n";
    cout << "6. Exit\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) {
      workSession.setSessionDuration(10);
      workSession.startTask("Work Session");
      quoteManager.startTask("Work Session");

      while (workSession.isTimerRunning()) {
        workSession.updateTimer();
        quoteManager.update();
        this_thread::sleep_for(chrono::seconds(1));
        ;
      }

      workSession.stopTask();
      quoteManager.stopTask();
    }

    else if (choice == 2) {
      breakSession.setSessionDuration(5);
      breakSession.startTask("Break Session");

      while (breakSession.isTimerRunning()) {
        breakSession.updateTimer();
        this_thread::sleep_for(chrono::seconds(1));
        ;
      }

      breakSession.stopTask();
    }

    else if (choice == 3) {
      quoteManager.display();
    }

    else if (choice == 4) {
      summary.readLogFile();
      summary.display();
      summary.showTaskDurations();
      summary.showTotalTimeSpent();
    }

    else if (choice == 5) {
      timerCount.resetTimerCount();
      for (int i = 0; i < 4; i++) {
        // === Work Session ===
        workSession.setSessionDuration(1500);  // demo = 10s
        workSession.startTask("Pomodoro Work " + to_string(i));
        quoteManager.startTask("Pomodoro Work");

        while (workSession.isTimerRunning()) {
          workSession.updateTimer();
          quoteManager.update();
          this_thread::sleep_for(chrono::seconds(1));
          ;
        }

        workSession.stopTask();
        quoteManager.stopTask();

        // === Break Session ===
        breakSession.setSessionDuration(300);  // demo = 5s
        breakSession.startTask("Pomodoro Break");

        while (breakSession.isTimerRunning()) {
          breakSession.updateTimer();
          this_thread::sleep_for(chrono::seconds(1));
          ;
        }

        breakSession.stopTask();
      }
    }

    else if (choice == 6) {
      cout << "Exiting Day 3 session. Stay productive!\n";
      break;
    }

    else {
      cout << "Invalid input. Try again.\n";
      return 0;
    }
  }

  return 0;
}
