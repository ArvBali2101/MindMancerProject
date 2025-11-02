#include "Authenticator.h"

// Constructor: Initializes the password and number of allowed attempts
Authenticator::Authenticator(string password, int noOfAttempts)
    : myPassword(password), myNoOfAttempts(noOfAttempts) {}

// Returns the stored password (used internally for comparison)
string Authenticator::getPassword() { return myPassword; }

// Validates the input password.
// Returns true if it matches; otherwise, decrements attempts and returns false.
bool Authenticator::authenticate(string password) {
  if (password == getPassword()) {
    return true;
  } else {
    myNoOfAttempts--;
    return false;
  }
}

// Returns the number of remaining authentication attempts
int Authenticator::getNoOfAttemptsLeft() { return myNoOfAttempts; }

// Displays the current authentication status (mainly for debugging)
void Authenticator::display() const {
  cout << "Password: " << myPassword << ", Attempts Left: " << myNoOfAttempts
       << endl;
}