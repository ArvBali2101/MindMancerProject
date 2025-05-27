#pragma once  // Prevents multiple inclusions of this header during compilation

#include <iostream>
#include <string>
using namespace std;

// Abstract base class that defines a common interface for task management.
// Any class inheriting from TaskManager must implement task start and stop
// behavior.
class TaskManager {
 public:
  // Starts a task with the given description.
  // Must be implemented by all derived classes.
  virtual void startTask(string taskDescription) = 0;

  // Stops the currently running task.
  // Must be implemented by all derived classes.
  virtual void stopTask() = 0;

  // Virtual destructor to ensure proper cleanup of derived classes
  virtual ~TaskManager() = default;
};