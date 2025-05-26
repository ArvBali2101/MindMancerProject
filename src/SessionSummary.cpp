#include "SessionSummary.h"

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

// Constructor: Initializes the summary with the path to the log file
SessionSummary::SessionSummary(const string& logFilename)
    : myFilename(logFilename) {}

// Converts a raw timestamp string to a time_t object
time_t SessionSummary::myParseTime(const string& rawTime) const {
  tm tm = {};
  istringstream ss(rawTime);
  ss >> get_time(&tm, "%a %b %d %H:%M:%S %Y");  // Expects format from ctime()
  return mktime(&tm);
}

// Reads the log file and extracts structured session data
void SessionSummary::readLogFile() {
  mySessions.clear();  // Reset previous session data
  ifstream file(myFilename);

  if (!file.is_open()) {
    cerr << "Failed to open log file: " << myFilename << endl;
    return;
  }

  string line;
  string currentTask;
  time_t sessionStart = 0;
  time_t sessionEnd = 0;
  time_t resumeTime = 0;
  time_t pauseTime = 0;
  bool inPause = false;
  time_t activeTime = 0;
  string timeOfTask;

  // Parse each line in the log file
  while (getline(file, line)) {
    istringstream iss(line);
    string taskWord1, taskWord2, action;
    iss >> taskWord1 >> taskWord2 >> action;

    // Construct task name and extract timestamp
    string taskName = taskWord1 + " " + taskWord2;
    size_t pos = line.find(action);
    string timeStr = line.substr(pos + action.size() + 1);
    timeOfTask = timeStr;
    time_t timestamp = myParseTime(timeStr);

    // Handle task event types
    if (action == "started") {
      currentTask = taskName;
      sessionStart = timestamp;
      resumeTime = timestamp;
      inPause = false;
      activeTime = 0;
    } else if (action == "Paused") {
      if (!inPause) {
        pauseTime = timestamp;
        activeTime += (pauseTime - resumeTime);
        inPause = true;
      }
    } else if (action == "Resumed") {
      if (inPause) {
        resumeTime = timestamp;
        inPause = false;
      }
    } else if (action == "ended") {
      sessionEnd = timestamp;
      if (!inPause) {
        activeTime += (sessionEnd - resumeTime);
      }
      // Store session summary
      mySessions.push_back(
          {currentTask, timeOfTask, sessionStart, sessionEnd, activeTime});
    }
  }

  file.close();
}

// Displays each session with its active time duration
void SessionSummary::showTaskDurations() const {
  cout << "\nSession Durations:\n";
  for (const auto& session : mySessions) {
    cout << "- " << session.taskName << " - " << session.taskTime << ": "
         << session.activeTime / 60 << " min (" << session.activeTime
         << " sec of active time)\n";
  }
}

// Displays the total active time spent across all sessions
void SessionSummary::showTotalTimeSpent() const {
  time_t total = 0;
  for (const auto& session : mySessions) {
    total += session.activeTime;
  }

  cout << "\nTotal Active Time Spent: " << total / 60 << " min (" << total
       << " sec)\n";
}

// Prints the raw contents of the log file
void SessionSummary::printLogFile() const {
  ifstream file(myFilename);
  if (!file.is_open()) {
    cerr << "Unable to open log file: " << myFilename << endl;
    return;
  }

  cout << "\n------ Task Log File ------\n";
  string line;
  while (getline(file, line)) {
    cout << line << "\n";
  }
  cout << "---------------------------\n";

  file.close();
}

// Displays summary metadata: file name and session count
void SessionSummary::display() const {
  cout << "Session Summary for: " << myFilename << endl;
  cout << "Total Sessions: " << mySessions.size() << endl;
}