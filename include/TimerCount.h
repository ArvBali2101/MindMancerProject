#pragma once  // Ensures the header is only included once

#include <iostream>
using namespace std;

// A simple utility class for tracking how many work sessions have occurred.
// Can be used to trigger breaks or track productivity.
class TimerCount {
 private:
  int myCount;  // Stores the number of completed work sessions

 public:
  // Constructor: Initializes the count to zero
  TimerCount();

  // Increments the session count by 1
  void incrementTimerCount();

  // Returns the current session count
  int getTimerCount();

  // Displays the current session count to the console
  void display() const;
};