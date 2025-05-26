#include <chrono>
#include <iostream>
#include <thread>

#include "BreakSessionManager.h"
#include "MotivationalQuoteManager.h"
#include "SessionConfigManager.h"
#include "SessionSummary.h"
#include "TaskLogger.h"
#include "TimerCount.h"
#include "WorkSessionManager.h"

using namespace std;

int main() {
  TimerCount timerCount;
  TaskLogger logger;
  logger.setLogFileName("day4_log.txt");

  SessionConfigManager config;

  // ✅ User-defined durations
  int workDuration;
  int breakDuration;

  cout << "Enter Work Duration in seconds (Default = 1500 for 25 min): ";
  cin >> workDuration;
  if (workDuration > 0) {
    config.setDefaultWorkDuration(workDuration);
  } else {
    cout << "Input invalid. Using default.\n";
  }

  cout << "Enter Break Duration in seconds (Default = 300 for 5 min): ";
  cin >> breakDuration;
  if (breakDuration > 0) {
    config.setDefaultBreakDuration(breakDuration);
  } else {
    cout << "Input invalid. Using default.\n";
  }

  WorkSessionManager workSession(logger, timerCount);
  BreakSessionManager breakSession(logger, timerCount);
  MotivationalQuoteManager quoteManager(10);  // every 10 sec
  SessionSummary summary("day4_log.txt");

  int choice;

  while (true) {
    cout << "\n==== MindMancer – Day 4 Menu ====\n";
    cout << "1. Start Work Session\n";
    cout << "2. Start Break Session\n";
    cout << "3. Show Motivational Quote Info\n";
    cout << "4. Show Session Summary\n";
    cout << "5. Run Full Pomodoro Cycle (4x)\n";
    cout << "6. Exit\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) {
      workSession.setSessionDuration(config.getDefaultWorkDuration());
      workSession.startTask("Work Session");
      quoteManager.startTask("Work Session");

      while (workSession.isTimerRunning()) {
        workSession.updateTimer();
        quoteManager.update();
        this_thread::sleep_for(chrono::milliseconds(500));
      }

      workSession.stopTask();
      quoteManager.stopTask();
    }

    else if (choice == 2) {
      breakSession.setSessionDuration(config.getDefaultBreakDuration());
      breakSession.startTask("Break Session");

      while (breakSession.isTimerRunning()) {
        breakSession.updateTimer();
        this_thread::sleep_for(chrono::milliseconds(500));
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
      for (int i = 0; i < 4; i++) {
        workSession.setSessionDuration(config.getDefaultWorkDuration());
        workSession.startTask("Pomodoro Work " + to_string(i));
        quoteManager.startTask("Pomodoro Work");

        while (workSession.isTimerRunning()) {
          workSession.updateTimer();
          quoteManager.update();
          this_thread::sleep_for(chrono::milliseconds(500));
        }

        workSession.stopTask();
        quoteManager.stopTask();

        breakSession.setSessionDuration(config.getDefaultBreakDuration());
        breakSession.startTask("Pomodoro Break");

        while (breakSession.isTimerRunning()) {
          breakSession.updateTimer();
          this_thread::sleep_for(chrono::milliseconds(500));
        }

        breakSession.stopTask();
      }
    }

    else if (choice == 6) {
      cout << "Exiting Day 4 session. Stay productive!\n";
      break;
    }

    else {
      cout << "Invalid input. Try again.\n";
    }
  }

  return 0;
}
