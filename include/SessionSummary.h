#pragma once  // Prevents multiple inclusion of this header file

#include <ctime>
#include <string>
#include <vector>
using namespace std;

// Parses and summarizes session data from a log file.
// Provides insights like task durations and total time spent.
class SessionSummary {
 private:
  string myFilename;  // Name of the log file to read

  // Represents a single logged session
  struct Session {
    string taskName;    // Name or description of the task
    string taskTime;    // Raw log line timestamp (as string)
    time_t startTime;   // Parsed start time
    time_t endTime;     // Parsed end time
    time_t activeTime;  // Time spent actively (excluding pauses)
  };

  vector<Session> mySessions;  // List of parsed session entries

  // Parses raw timestamp string into a time_t object
  time_t myParseTime(const string& rawTime) const;

 public:
  // Constructor: Initializes with the given log filename
  SessionSummary(const string& logFilename);

  // Reads and parses the session data from the log file
  void readLogFile();

  // Displays individual task durations
  void showTaskDurations() const;

  // Displays total active time across all sessions
  void showTotalTimeSpent() const;

  // Prints the entire raw log file to the console
  void printLogFile() const;

  // Displays a summary of the session data
  void display() const;
};
