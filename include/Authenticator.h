#pragma once  // Prevents multiple inclusion of this header file

#include <iostream>
#include <string>
using namespace std;

// Class responsible for handling user authentication using a password.
// Tracks the number of remaining login attempts.
class Authenticator {
 private:
  string myPassword;   // Stored password for validation
  int myNoOfAttempts;  // Number of attempts remaining

  // Returns the stored password (used internally)
  string getPassword();

 public:
  // Constructor to initialize the password and allowed attempts
  Authenticator(string password, int noOfAttempts);

  // Verifies the input password against the stored one
  bool authenticate(string password);

  // Returns the number of remaining attempts
  int getNoOfAttemptsLeft();

  // Displays authentication status (optional for debug/logging)
  void display() const;
};