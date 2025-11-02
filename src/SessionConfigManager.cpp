#include "SessionConfigManager.h"

// Constructor: sets default durations (e.g., 25 min work, 5 min break)
SessionConfigManager::SessionConfigManager()
    : defaultWorkDuration(1500),  // 1500s = 25 minutes
      defaultBreakDuration(300)   // 300s = 5 minutes
{}

// Set default work session duration (in seconds)
void SessionConfigManager::setDefaultWorkDuration(int seconds) {
  defaultWorkDuration = seconds;
}

// Set default break session duration (in seconds)
void SessionConfigManager::setDefaultBreakDuration(int seconds) {
  defaultBreakDuration = seconds;
}

// Get default work session duration
int SessionConfigManager::getDefaultWorkDuration() const {
  return defaultWorkDuration;
}

// Get default break session duration
int SessionConfigManager::getDefaultBreakDuration() const {
  return defaultBreakDuration;
}