#include "TaskLogger.h"

// Constructor: Initializes the logger with empty task description and log file
// name
TaskLogger::TaskLogger() : myLogFileName(""), myTaskDescription("") {}

// Destructor: Ensures the log file is closed if still open
TaskLogger::~TaskLogger() {
  if (myLogFile.is_open()) {
    myLogFile.close();
  }
}

// Sets the task description (used internally)
void TaskLogger::setTaskDescription(string taskDescription) {
  myTaskDescription = taskDescription;
}

// Returns the current task description
string TaskLogger::getTaskDescription() { return myTaskDescription; }

// Begins logging for a task and appends the start time to the log file
void TaskLogger::startLogging(string taskDescription) {
  setTaskDescription(taskDescription);
  myLogFile.open(myLogFileName, ios::app);  // Open in append mode

  if (!myLogFile) {
    cerr << "Error opening log file.\n";
    return;
  }

  time_t now = time(nullptr);
  myLogFile << "################################################" << "\n";
  myLogFile << getTaskDescription() << " started " << ctime(&now);
}

// Logs a specific stage of the task (e.g., "paused", "resumed")
void TaskLogger::logTask(string stage) {
  time_t now = time(nullptr);
  myLogFile << getTaskDescription() << " " << stage << " " << ctime(&now);
}

// Ends the current task log and writes the end time
void TaskLogger::stopLogging() {
  time_t now = time(nullptr);
  myLogFile << getTaskDescription() << " ended " << ctime(&now);
  myLogFile << "################################################" << "\n";
  myLogFile.close();
}

// Sets the name of the log file to use for writing logs
void TaskLogger::setLogFileName(string logFileName) {
  myLogFileName = logFileName;
}

// Returns the current log file name
string TaskLogger::getLogFileName() const { return myLogFileName; }

// Displays current logger configuration (for debug or info)
void TaskLogger::display() const {
  cout << "Task Description: " << myTaskDescription << endl;
  cout << "Log File Name: " << myLogFileName << endl;
}