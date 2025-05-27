#pragma once

#include <ctime>
#include <fstream>

#include "TaskManager.h"

using namespace std;

// Class responsible for handling task logging operations.
// Logs task start, stop, and progress information into a file.
class TaskLogger {
  ofstream myLogFile;        // Output file stream for logging
  string myLogFileName;      // Name of the log file
  string myTaskDescription;  // Description of the current task

  // Sets the description for the current task (used internally)
  void setTaskDescription(string taskDescription);

 public:
  // Constructor: Initializes logger state
  TaskLogger();

  // Destructor: Ensures file streams are properly closed
  ~TaskLogger();

  // Sets the name of the log file to use
  void setLogFileName(string logFileName);

  // Returns the current log file name
  string getLogFileName() const;

  // Returns the description of the current task
  string getTaskDescription();

  // Starts logging for a new task
  void startLogging(string taskDescription);

  // Logs a specific stage (e.g., "STARTED", "PAUSED", "STOPPED")
  void logTask(string stage);

  // Ends logging for the current task
  void stopLogging();

  // Displays log file contents to the console
  void display() const;
};