#include "Authenticator.h"

int main()
{
    // Create an Authenticator with the correct password and 3 allowed attempts
    Authenticator myAuthenticator("welcome", 3);
    string userInput;

    // Show the initial number of attempts
    cout << "\033[34mInitial attempts left: "
         << myAuthenticator.getNoOfAttemptsLeft() << "\033[0m" << endl;

    // Keep asking for password until success or attempts run out
    while (myAuthenticator.getNoOfAttemptsLeft() > 0)
    {
        cout << "Enter password: ";
        cin >> userInput;

        if (myAuthenticator.authenticate(userInput))
        {
            cout << "\033[32m✅ User Authenticated\033[0m" << endl;
            break;
        }
        else
        {
            cout << "\033[31m❌ Incorrect Password. Attempts left: "
                 << myAuthenticator.getNoOfAttemptsLeft() << "\033[0m" << endl;
        }
    }

    // If attempts used up, deny access
    if (myAuthenticator.getNoOfAttemptsLeft() == 0)
    {
        cout << "\033[1;31m⛔ Invalid user - Access Denied\033[0m" << endl;
    }

    return 0;
}
