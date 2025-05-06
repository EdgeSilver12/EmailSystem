#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct User {
    string username;
    string password;
};

struct Message {
    string sender;
    string recipient;
    string content;
};

// Check if a user exists in the users file
bool userExists(const string& username) {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string existingUser, existingPass;
        getline(ss, existingUser, ',');
        if (existingUser == username) {
            return true;
        }
    }
    return false;
}

// Register a new user
bool registerUser() {
    User user;
    cout << "\n--- Register ---\n";
    cout << "Choose a username: ";
    cin >> user.username;

    if (userExists(user.username)) {
        cout << "Username already exists. Try again.\n";
        return false;
    }

    cout << "Choose a password: ";
    cin >> user.password;

    ofstream file("users.txt", ios::app);
    file << user.username << "," << user.password << endl;
    file.close();

    cout << "Registration successful!\n";
    return true;
}

// Login user
bool loginUser(User &loggedInUser) {
    cout << "\n--- Login ---\n";
    cout << "Username: ";
    cin >> loggedInUser.username;
    cout << "Password: ";
    cin >> loggedInUser.password;

    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string user, pass;
        getline(ss, user, ',');
        getline(ss, pass, '\n');

        if (user == loggedInUser.username && pass == loggedInUser.password) {
            cout << "Login successful! Welcome, " << loggedInUser.username << ".\n";
            return true;
        }
    }

    cout << "Invalid username or password.\n";
    return false;
}

// Function to send a message
void sendMessage(User sender) {
    Message message;
    message.sender = sender.username;

    cout << "Enter the recipient's username: ";
    cin >> message.recipient;

    cout << "Enter your message: ";
    cin.ignore();  // to clear the input buffer
    getline(cin, message.content);

    ofstream file("messages.txt", ios::app);
    file << message.sender << "," << message.recipient << "," << message.content << endl;
    file.close();

    cout << "Message sent to " << message.recipient << "!\n";
}

// Function to check inbox for messages
void checkInbox(User recipient) {
    ifstream file("messages.txt");
    string line;
    bool foundMessages = false;

    cout << "\n--- Inbox ---\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string sender, recipientInFile, content;
        getline(ss, sender, ',');
        getline(ss, recipientInFile, ',');
        getline(ss, content, '\n');

        if (recipientInFile == recipient.username) {
            foundMessages = true;
            cout << "From: " << sender << "\nMessage: " << content << "\n---\n";
        }
    }

    if (!foundMessages) {
        cout << "No new messages.\n";
    }
}

// Show the main menu after logging in
void showMainMenu(User user) {
    int choice;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Send Message\n";
        cout << "2. Check Inbox\n";
        cout << "3. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                sendMessage(user);
                break;
            case 2:
                checkInbox(user);
                break;
            case 3:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

// Main function to control the flow of the program
int main() {
    int choice;
    User currentUser;

    do {
        cout << "\n=== Email System ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser(currentUser)) {
                    showMainMenu(currentUser);
                }
                break;
            case 3:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
