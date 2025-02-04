//
// created by Hafsa Farid on 24/12/2024.
//
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// Structure to represent a bank account
struct Account {
    string name;           // Account holder's name
    string accountNumber;  // Unique account number
    double balance{};        // Account balance
};

// Function to create a new account
void createAccount() {
    Account newAccount;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, newAccount.name);

    cout << "Enter account number: ";
    cin >> newAccount.accountNumber;

    cout << "Enter initial deposit amount: ";
    cin >> newAccount.balance;

    // Validate initial deposit amount
    if (newAccount.balance < 0) {
        cout << "Initial deposit cannot be negative." << endl;
        return;
    }

    // Check for unique account number
    ifstream inputFile("accounts.txt");
    Account temp;
    while (inputFile >> temp.name >> temp.accountNumber >> temp.balance) {
        if (temp.accountNumber == newAccount.accountNumber) {
            cout << "Account number already exists. Please use a unique account number." << endl;
            inputFile.close();
            return;
        }
    }
    inputFile.close();

    // Save new account details to the file
    ofstream outputFile("accounts.txt", ios::app);
    outputFile << newAccount.name << " " << newAccount.accountNumber << " " << newAccount.balance << endl;
    outputFile.close();

    cout << "Account created successfully!" << endl;
}

// Function to deposit money into an account
void deposit() {
    string accountNumber;
    double amount;
    cout << "Enter account number: ";
    cin >> accountNumber;

    cout << "Enter amount to deposit: ";
    cin >> amount;

    // Validate deposit amount
    if (amount < 0) {
        cout << "Deposit amount cannot be negative." << endl;
        return;
    }

    ifstream inputFile("accounts.txt");
    ofstream tempFile("temp.txt");
    bool found = false;
    Account temp;

    // Update account balance if the account number matches
    while (inputFile >> temp.name >> temp.accountNumber >> temp.balance) {
        if (temp.accountNumber == accountNumber) {
            temp.balance += amount;
            found = true;
            cout << "Deposit successful! Updated balance: " << temp.balance << endl;
        }
        tempFile << temp.name << " " << temp.accountNumber << " " << temp.balance << endl;
    }

    inputFile.close();
    tempFile.close();

    // Replace the old file with the updated file
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) {
        cout << "Account number not found." << endl;
    }
}

// Function to withdraw money from an account
void withdraw() {
    string accountNumber;
    double amount;
    cout << "Enter account number: ";
    cin >> accountNumber;

    cout << "Enter amount to withdraw: ";
    cin >> amount;

    // Validate withdrawal amount
    if (amount < 0) {
        cout << "Withdrawal amount cannot be negative." << endl;
        return;
    }

    ifstream inputFile("accounts.txt");
    ofstream tempFile("temp.txt");
    bool found = false;
    Account temp;

    // Deduct amount from balance if sufficient funds are available
    while (inputFile >> temp.name >> temp.accountNumber >> temp.balance) {
        if (temp.accountNumber == accountNumber) {
            if (temp.balance >= amount) {
                temp.balance -= amount;
                found = true;
                cout << "Withdrawal successful! Updated balance: " << temp.balance << endl;
            } else {
                cout << "Insufficient balance." << endl;
                tempFile << temp.name << " " << temp.accountNumber << " " << temp.balance << endl;
                continue;
            }
        }
        tempFile << temp.name << " " << temp.accountNumber << " " << temp.balance << endl;
    }

    inputFile.close();
    tempFile.close();

    // Replacing the old file with the updated file
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) {
        cout << "Account number not found." << endl;
    }
}

// Function to check account details
void checkDetails() {
    string accountNumber;
    cout << "Enter account number: ";
    cin >> accountNumber;

    ifstream inputFile("accounts.txt");
    Account temp;
    bool found = false;

    // Display account details if the account number matches
    while (inputFile >> temp.name >> temp.accountNumber >> temp.balance) {
        if (temp.accountNumber == accountNumber) {
            cout << "Name: " << temp.name << endl;
            cout << "Account Number: " << temp.accountNumber << endl;
            cout << "Balance: " << fixed << setprecision(2) << temp.balance << endl;
            found = true;
            break;
        }
    }

    inputFile.close();

    if (!found) {
        cout << "Account number not found." << endl;
    }
}

// Main function to display the menu and handle user input
int main() {
    int choice;

    do {
        cout << "\nWelcome to Simple Bank System" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Check Account Details" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Call the corresponding function based on user choice
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkDetails();
                break;
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}