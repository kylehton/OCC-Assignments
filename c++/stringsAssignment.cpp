#include <iostream>
#include <string>
using namespace std;

// Function to check if password is valid
bool isValidPassword(const string& password) {
    // Check password length
    if (password.length() < 6) {
        cout << "Password must be at least 6 characters long." << endl;
        return false;
    }

    // Check for uppercase letter requirement
    bool hasUppercase = false;
    for (char c : password) {
        if (isupper(c)) {
            hasUppercase = true;
            break;
        }
    }
    if (!hasUppercase) {
        cout << "Password must contain at least one uppercase letter." << endl;
        return false;
    }

    // Check for lowercase letter requirement
    bool hasLowercase = false;
    for (char c : password) {
        if (islower(c)) {
            hasLowercase = true;
            break;
        }
    }
    if (!hasLowercase) {
        cout << "Password must contain at least one lowercase letter." << endl;
        return false;
    }

    // Check for digit requirement
    bool hasDigit = false;
    for (char c : password) {
        if (isdigit(c)) {
            hasDigit = true;
            break;
        }
    }
    if (!hasDigit) {
        cout << "Password must contain at least one digit." << endl;
        return false;
    }

    // All criteria met
    return true;
}

int main() {
    // declare password variable
    string password;

    // print password requirements to be valid
    cout << "Password requirements:\n";
    cout << "- At least 6 characters long\n";
    cout << "- At least one uppercase letter\n";
    cout << "- At least one lowercase letter\n";
    cout << "- At least one digit\n\n";
    
    // prompt user for password
    cout << "Enter your password: ";
    getline(cin, password);
    
    // call function to check if password is valid
    bool isValid = isValidPassword(password);
    // ternary op to print whether successful or not based on function return
    cout << (isValid ? "Password accepted!" : "Password not accepted!") << endl;
    
    return 0;
}