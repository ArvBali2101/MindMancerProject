#include <chrono>
#include <iostream>
#include <thread>

#include "Authenticator.h"
#include "BreakSessionManager.h"
#include "MotivationalQuoteManager.h"
#include "SessionConfigManager.h"
#include "SessionManager.h"
#include "SessionSummary.h"
#include "TaskLogger.h"
#include "TimerCount.h"
#include "WorkSessionManager.h"

using namespace std;

int main() {
  Authenticator* auth = new Authenticator("welcome", 3);
  string inputPassword;

  while (auth->getNoOfAttemptsLeft() > 0) {
    cout << "Enter password to continue: ";
    cin >> inputPassword;
    if (auth->authenticate(inputPassword)) {
      cout << "\033[32m✅ User Authenticated\033[0m" << endl;
      cout << "Welcome to MindMancer... " << endl;
      break;
    } else {
      if (auth->getNoOfAttemptsLeft() > 0) {
        cout << "\033[31m❌ Incorrect Password. Attempts left: "
             << auth->getNoOfAttemptsLeft() << "\033[0m" << endl;
      } else {
        cout << "\033[1;31m⛔ Invalid user - Access Denied\033[0m" << endl;
        return 1;
      }
    }
  }

  TimerCount timerCount;
  TaskLogger logger;
  logger.setLogFileName("day4_log.txt");

  SessionConfigManager config;
  int workDuration;
  int breakDuration;

  cout << "Enter Work Duration (Default 25 mins) in seconds:" << endl;
  cin >> workDuration;
  if (workDuration > 0) {
    config.setDefaultWorkDuration(workDuration);
  } else {
    cout << "Input value is less than 0.. setting default" << endl;
  }

  cout << "Enter Break Duration (Default 5 mins) in seconds:" << endl;
  cin >> breakDuration;

  if (breakDuration > 0) {
    config.setDefaultBreakDuration(breakDuration);
  } else {
    cout << "Input value is less than 0.. setting default" << endl;
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
          this_thread::sleep_for(chrono::seconds(1));
        }

        workSession->stopTask();
        quoteManager->stopTask();
        break;

      case 2:
        breakSession->setSessionDuration(config.getDefaultBreakDuration());
        breakSession->startTask("Break Session");

        while (breakSession->isTimerRunning()) {
          breakSession->updateTimer();
          this_thread::sleep_for(chrono::seconds(1));
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
            this_thread::sleep_for(chrono::seconds(1));
          }

          workSession->stopTask();
          quoteManager->stopTask();

          // === Break Session ===
          breakSession->setSessionDuration(config.getDefaultBreakDuration());
          breakSession->startTask("Pomodoro Break");

          while (breakSession->isTimerRunning()) {
            breakSession->updateTimer();
            this_thread::sleep_for(chrono::seconds(1));
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

  if (auth != nullptr) delete auth;
  if (workSession != nullptr) delete workSession;
  if (breakSession != nullptr) delete breakSession;
  if (quoteManager != nullptr) delete quoteManager;
  if (summary != nullptr) delete summary;

  return 0;
}
