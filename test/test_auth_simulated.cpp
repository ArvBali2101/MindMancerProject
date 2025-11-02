#include "Authenticator.h"

int main() {
  // Create an Authenticator object with password "welcome" and 3 allowed
  // attempts
  Authenticator myAuthenticator("welcome", 3);

  // Simulated user inputs for testing authentication
  string testPassword[] = {"welcome1", "welcome1", "welcome"};

  int count = 0;

  // Display initial number of attempts (Blue)
  cout << "\033[34mInitial attempts left: "
       << myAuthenticator.getNoOfAttemptsLeft() << "\033[0m" << endl;

  // Loop until the user is authenticated or attempts run out
  while (myAuthenticator.getNoOfAttemptsLeft() > 0) {
    if (myAuthenticator.authenticate(testPassword[count])) {
      // Success (Green)
      cout << "\033[32m✅ User Authenticated\033[0m" << endl;
      break;
    } else {
      // Failure (Red)
      cout << "\033[31m❌ Incorrect Password. No of attempts left: "
           << myAuthenticator.getNoOfAttemptsLeft() << "\033[0m" << endl;
      count++;
    }
  }

  // Final check: if all attempts are used up, deny access (Bright Red)
  if (myAuthenticator.getNoOfAttemptsLeft() == 0) {
    cout << "\033[1;31m⛔ Invalid user - Access Denied\033[0m" << endl;
  }

  return 0;
}
