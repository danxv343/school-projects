#include <iostream>
#include <cstring>
#include <string>
#include <ctime>

using namespace std;

int main() {
    const int MAX_ACCOUNTS = 100;
    string accountNumbers[MAX_ACCOUNTS];
    string accountHolders[MAX_ACCOUNTS];
    int phoneNumbers[MAX_ACCOUNTS];
    string emailAddresses[MAX_ACCOUNTS];
    string pins[MAX_ACCOUNTS];
    double balances[MAX_ACCOUNTS];
    string transactionHistory[MAX_ACCOUNTS];
    int numAccounts = 0;

    srand(time(NULL));

    while (true) {
        // Main home page code
        cout << "=== Banking App ===" << endl;
        cout << "1. Create a new bank account" << endl;
        cout << "2. Sign in" << endl;
        cout << "0. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Account creation code
                if (numAccounts == MAX_ACCOUNTS) {
                    cout << "Maximum number of accounts reached." << endl;
                } else {
                    int accountNumber = rand() % 9000000000 + 1000000000; // Generate random 10-digit account number
                    accountNumbers[numAccounts] = to_string(accountNumber);
                    cout << "Generated Account Number: " << accountNumbers[numAccounts] << endl;

                    cout << "Enter account holder's Full name: ";
                    cin.ignore();
                    getline(cin, accountHolders[numAccounts]);

                    cout << "Enter phone number: ";
                    cin >> phoneNumbers[numAccounts];

                    cout << "Enter email address: ";
                    cin >> emailAddresses[numAccounts];

                    cout << "Enter initial balance: ";
                    cin >> balances[numAccounts];

                    cout << "Create a 4-digit PIN: ";
                    cin >> pins[numAccounts];

                    numAccounts++;
                    cout << "Account created successfully." << endl;
                }
                break;
            }
            case 2: {
                // Sign-in process code
                string accountNumber;
                string pin;
                cout << "Enter account number: ";
                cin >> accountNumber;

                int accountIndex = -1;
                for (int i = 0; i < numAccounts; i++) {
                    if (accountNumbers[i] == accountNumber) {
                        accountIndex = i;
                        break;
                    }
                }

                if (accountIndex == -1) {
                    cout << "Invalid account number." << endl;
                } else {
                    int attempts = 4;
                    bool isAuthenticated = false;

                    while (attempts > 0) {
                        cout << "Enter PIN: ";
                        cin >> pin;

                        if (pins[accountIndex] == pin) {
                            isAuthenticated = true;
                            break;
                        } else {
                            attempts--;
                            cout << "Invalid PIN. Please try again. " << attempts << " attempts remaining." << endl;
                        }
                    }

                    if (!isAuthenticated) {
                        cout << "Exceeded maximum attempts. Please contact customer support to reset your PIN." << endl;
                    } else {
                        // User authenticated successfully, proceed with account menu
                        while (true) {
                            // Main menu code
                            cout << endl;
                            cout << "=== Account Menu ===" << endl;
                            cout << "1. Deposit money" << endl;
                            cout << "2. Withdraw money" << endl;
                            cout << "3. Transfer money" << endl;
                            cout << "4. View account balance" << endl;
                            cout << "5. View transaction history" << endl;
                            cout << "6. Modify account details" << endl;
                            cout << "7. Calculate interest on savings accounts" << endl;
                            cout << "8. Handle multiple currencies and exchange rates" << endl;
                            cout << "0. Sign out" << endl;

                            int accountChoice;
                            cout << "Enter your choice: ";
                            cin >> accountChoice;

                            switch (accountChoice) {
                                case 1: {
                                // Deposit money code
                                    double amount;
                                    cout << "Enter amount to deposit: ";
                                    cin >> amount;
                                    balances[accountIndex] += amount;

                                    // Get the current time
                                    time_t now = time(0);
                                    char* dt = ctime(&now);
                                    transactionHistory[accountIndex] += "Deposited " + to_string(amount) + " Birr into the account. Time: " + string(dt) + "\n";
                                    cout << "Deposit successful." << endl;
                                    break;
                                }
                                case 2: {
                                // Withdraw money code
                                    double amount;
                                    cout << "Enter amount to withdraw: ";
                                    cin >> amount;
                                    if (balances[accountIndex] >= amount) {
                                        balances[accountIndex] -= amount;
                                    
                                    // Get the current time
                                    time_t now = time(0);
                                    char* dt = ctime(&now);
                                    transactionHistory[accountIndex] += "Withdrawn " + to_string(amount) + " Birr from the account. Time: " + string(dt) + "\n";
                                    cout << "Withdrawal successful." << endl;
                                    } else {
                                        cout << "Insufficient funds." << endl;
                                    }
                                    break;
                                }
                                case 3: {
                                // Transfer money code
                                    string destinationAccountNumber;
                                    double amount;
                                    cout << "Enter destination account number: ";
                                    cin >> destinationAccountNumber;
                                    cout << "Enter amount to transfer: ";
                                    cin >> amount;

                                    int destinationIndex = -1;
                                    for (int i = 0; i < numAccounts; i++) {
                                        if (accountNumbers[i] == destinationAccountNumber) {
                                            destinationIndex = i;
                                            break;
                                        }
                                    }
                                    if (destinationIndex == -1) {
                                        cout << "Invalid destination account number." << endl;
                                    } else if (balances[accountIndex] < amount) {
                                        cout << "Insufficient funds in the source account." << endl;
                                    } else {
                                        balances[accountIndex] -= amount;
                                        balances[destinationIndex] += amount;
                                        
                                        // Get the current time
                                        time_t now = time(0);
                                        char* dt = ctime(&now);
                                        transactionHistory[accountIndex] += "Transferred " + to_string(amount) + " Birr to account " + destinationAccountNumber + ". Time: " + string(dt) + "\n";
                                        transactionHistory[destinationIndex] += "Received " + to_string(amount) + " Birr from account " + accountNumbers[accountIndex] + ". Time: " + string(dt) + "\n";
                                        cout << "Transfer successful." << endl;
                                    }
                                    break;
                                }
                                case 4: {
                                    // Account Balance check code
                                    cout << "Account balance: " << balances[accountIndex] << " Birr.\n" << endl;
                                    break;
                                }
                                case 5: {
                                    // Transaction history display code
                                    cout << "Transaction history:" << endl;
                                    cout << transactionHistory[accountIndex] << endl;
                                    break;
                                }
                                case 6: {
                                    // Account detail modification code
                                    cout << "Enter new account holder's name: ";
                                    cin.ignore();
                                    getline(cin, accountHolders[accountIndex]);
                                    cout << "Enter new phone number: ";
                                    cin >> phoneNumbers[accountIndex];
                                    cout << "Enter new email address: ";
                                    cin >> emailAddresses[accountIndex];
                                    cout << "Account details modified successfully." << endl;
                                    break;
                                }
                                case 7: {
                                    // Interest rate calculation code
                                    double interestRate = 0.05;
                                    double interest = balances[accountIndex] * interestRate;
                                    balances[accountIndex] += interest;
                                    cout << "Interest calculated and added to the account." << endl;
                                    break;
                                }
                                case 8: {
                                    // Currency conversion code
                                    cout << "Choose a currency to convert to:" << endl;
                                    cout << "1. USD" << endl;
                                    cout << "2. EUR" << endl;
                                    cout << "3. GBP" << endl;
                                    cout << "4. JPY" << endl;
                                    cout << "5. AUD" << endl;
                                    cout << "Enter your choice: ";

                                    int currencyChoice;
                                    cin >> currencyChoice;

                                    double conversionRate;
                                    double amount;
                                    switch (currencyChoice) {
                                        case 1: // USD
                                            conversionRate = 1.2;
                                            break;
                                        case 2: // EUR
                                            conversionRate = 1.1;
                                            break;
                                        case 3: // GBP
                                            conversionRate = 1.4;
                                            break;
                                        case 4: // JPY
                                            conversionRate = 0.0095;
                                            break;
                                        case 5: // AUD
                                            conversionRate = 0.85;
                                            break;
                                        default:
                                            cout << "Invalid currency choice." << endl;
                                            continue;
                                    }
                                    
                                    cout << "Enter amount to convert: ";
                                    cin >> amount;
                                    if (amount <= 0) {
                                    cout << "Invalid amount." << endl;
                                    } else {
                                        double convertedAmount = amount * conversionRate;
                                        balances[accountIndex] += convertedAmount;
                                        cout << "Amount converted and added to the account." << endl;
                                    }
                                    break;
                                }
                                case 0: {
                                    // Sign-out code
                                    system("CLS");
                                    cout << "Signed out successfully." << endl;
                                    break;
                                }
                                default: {
                                    cout << "Invalid choice. Please try again." << endl;
                                    break;
                                }
                            }
                            if (accountChoice == 0) {
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case 0: {
                // Program exit code
                system("CLS");
                cout << "Thank you for using the Banking App. Goodbye!" << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }

        cout << endl;
    }
    return 0;
}
