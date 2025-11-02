#ifndef SESSIONCONFIGMANAGER_H
#define SESSIONCONFIGMANAGER_H

// SessionConfigManager handles default durations for work and break sessions.
class SessionConfigManager {
 private:
  int defaultWorkDuration;   // Default work session duration (in seconds)
  int defaultBreakDuration;  // Default break session duration (in seconds)

 public:
  // Constructor sets default durations
  SessionConfigManager();

  // Setters
  void setDefaultWorkDuration(int seconds);
  void setDefaultBreakDuration(int seconds);

  // Getters
  int getDefaultWorkDuration() const;
  int getDefaultBreakDuration() const;
};

#endif
