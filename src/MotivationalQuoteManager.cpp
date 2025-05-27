#include "MotivationalQuoteManager.h"

#include <cstdlib>
#include <iostream>

// Constructor: Initializes state and populates the quote list
MotivationalQuoteManager::MotivationalQuoteManager(int quoteIntervalSeconds)
    : myIsRunning(false),
      myLastQuoteTime(0),
      myQuoteIntervalSeconds(quoteIntervalSeconds) {
  // Predefined list of motivational quotes
  myQuotes = {
      "Keep pushing forward!",
      "You're doing great!",
      "Stay focused and never give up!",
      "Every step counts!",
      "Success comes from consistency!",
      "Discipline beats motivation.",
      "One day or day one. You decide.",
      "Do it now. Sometimes later becomes never.",
      "You don't have to be extreme, just consistent.",
      "Your only limit is your mind.",
      "Don't watch the clock; do what it does. Keep going.",
      "Push yourself, because no one else is going to do it for you.",
      "Small progress is still progress.",
      "You are stronger than you think.",
      "Winners are not people who never fail, but people who never quit.",
      "Make it happen. Shock everyone.",
      "If you get tired, learn to rest, not to quit.",
      "The pain you feel today will be the strength you feel tomorrow.",
      "Grind in silence. Let success make the noise."};

  // Seed the random number generator
  srand(time(nullptr));
}

// Destructor: destroys the object
MotivationalQuoteManager::~MotivationalQuoteManager() {}

// Starts the motivational quote session and resets the last quote timer
void MotivationalQuoteManager::startTask(string name) {
  myTaskName = name;
  myIsRunning = true;
  myLastQuoteTime = time(nullptr);
  cout << "Started motivational quotes for: " << myTaskName << endl;
}

// Stops the quote session
void MotivationalQuoteManager::stopTask() {
  myIsRunning = false;
  cout << "Stopped motivational quotes for: " << myTaskName << endl;
}

// Checks whether it’s time to show a new quote and displays one if due
void MotivationalQuoteManager::update() {
  if (!myIsRunning) return;

  time_t now = time(nullptr);
  if (now - myLastQuoteTime >= myQuoteIntervalSeconds) {
    int index = rand() % myQuotes.size();
    cout << "[Motivation] " << myQuotes[index] << endl;
    myLastQuoteTime = now;
  }
}

// Displays internal state for debugging or monitoring
void MotivationalQuoteManager::display() const {
  cout << "Current Task: " << myTaskName << endl;
  cout << "Is Running: " << (myIsRunning ? "Yes" : "No") << endl;
  cout << "Last Quote Time: " << ctime(&myLastQuoteTime);
  cout << "Quote Interval: " << myQuoteIntervalSeconds << " seconds" << endl;
}