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
  logger.setLogFileName("day3_log.txt");

  SessionConfigManager config;
  int workDuration;
  int breakDuration;

  cout << "Enter Work Duration (Default 25 mins) in seconds" << endl;
  cin >> workDuration;
  if (workDuration > 0) {
    config.setDefaultWorkDuration(workDuration);
  } else {
    cout << "Invalid or zero input. Setting to default (25 mins)." << endl;
  }

  cout << "Enter Break Duration (Default 5 mins) in seconds" << endl;
  cin >> breakDuration;

  if (breakDuration > 0) {
    config.setDefaultBreakDuration(breakDuration);
  } else {
    cout << "Invalid or zero input. Setting to default (5 mins)." << endl;
  }

  SessionManager* workSession = new WorkSessionManager(logger, timerCount);
  SessionManager* breakSession = new BreakSessionManager(logger, timerCount);
  MotivationalQuoteManager* quoteManager =
      new MotivationalQuoteManager(10);  // every 10 sec
  SessionSummary* summary = new SessionSummary("day3_log.txt");

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
    switch (choice) {
      case 1:
        workSession->setSessionDuration(config.getDefaultWorkDuration());
        workSession->startTask("Work Session");
        quoteManager->startTask("Work Session");

        while (workSession->isTimerRunning()) {
          workSession->updateTimer();
          quoteManager->update();
          this_thread::sleep_for(chrono::milliseconds(500));
          ;
        }

        workSession->stopTask();
        quoteManager->stopTask();
        break;

      case 2:
        breakSession->setSessionDuration(config.getDefaultBreakDuration());
        breakSession->startTask("Break Session");

        while (breakSession->isTimerRunning()) {
          breakSession->updateTimer();
          this_thread::sleep_for(chrono::milliseconds(500));
          ;
        }

        breakSession->stopTask();
        break;

      case 3:
        quoteManager->display();
        break;

      case 4:
        summary->readLogFile();
        summary->display();
        summary->showTaskDurations();
        summary->showTotalTimeSpent();
        break;

      case 5:
        timerCount.resetTimerCount();
        for (int i = 0; i < 4; i++) {
          // === Work Session ===
          workSession->setSessionDuration(config.getDefaultWorkDuration());
          workSession->startTask("Pomodoro Work " + to_string(i));
          quoteManager->startTask("Pomodoro Work");

          while (workSession->isTimerRunning()) {
            workSession->updateTimer();
            quoteManager->update();
            this_thread::sleep_for(chrono::milliseconds(500));
            ;
          }

          workSession->stopTask();
          quoteManager->stopTask();

          // === Break Session ===
          breakSession->setSessionDuration(config.getDefaultBreakDuration());
          breakSession->startTask("Pomodoro Break");

          while (breakSession->isTimerRunning()) {
            breakSession->updateTimer();
            this_thread::sleep_for(chrono::milliseconds(500));
            ;
          }

          breakSession->stopTask();
        }
        break;

      case 6:
        cout << "Exiting Day 3 session. Stay productive!\n";
        return 0;

      default:
        cout << "Invalid input. Try again.\n";
        return 0;
    }
  }

  delete workSession;
  delete breakSession;
  delete quoteManager;
  delete summary;

  return 0;
}
