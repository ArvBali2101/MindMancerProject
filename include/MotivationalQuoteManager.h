#pragma once  // Prevents multiple inclusion of this header file

#include <ctime>
#include <string>
#include <vector>

#include "TaskManager.h"

using namespace std;

// Displays motivational quotes at set time intervals during a session.
// Inherits from TaskManager to stay consistent with the task lifecycle.
class MotivationalQuoteManager : public TaskManager {
 private:
  vector<string> myQuotes;     // Collection of motivational quotes
  string myTaskName;           // Task name associated with the quote session
  bool myIsRunning;            // True if quote display is active
  time_t myLastQuoteTime;      // Time when the last quote was shown
  int myQuoteIntervalSeconds;  // Interval between quote displays (in seconds)

 public:
  // Constructor: Sets how often to show quotes
  MotivationalQuoteManager(int quoteIntervalSeconds);

  // Starts the quote display session
  void startTask(string taskName) override;

  // Stops the quote display session
  void stopTask() override;

  // Updates quote display based on time passed
  void update();

  // Displays current session or quote status
  void display() const;
};