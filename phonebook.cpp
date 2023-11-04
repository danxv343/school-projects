#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

const int MAX_CONTACTS = 1000;

// ANSI color codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";

struct Contact {
    int id;
    char firstName[21];  // One extra character for null terminator
    char lastName[21];   // One extra character for null terminator
    char gender;
    char phoneNumber[12];  // One extra character for null terminator
};

void listContacts(const Contact contacts[], int contactCount) {
    for (int i = 0; i < contactCount; ++i) {
        cout << BLUE << "ID: " << RESET << contacts[i].id << "\n";
        cout << BLUE << "First Name: " << RESET << contacts[i].firstName << "\n";
        cout << BLUE << "Last Name: " << RESET << contacts[i].lastName << "\n";
        cout << BLUE << "Gender: " << RESET << contacts[i].gender << "\n";
        cout << BLUE << "Phone Number: " << RESET << contacts[i].phoneNumber << "\n";
        cout << YELLOW << "------------------------------------\n" << RESET;
    }
}

void searchContact(const Contact contacts[], int contactCount, const char* fullName) {
    bool found = false;
    for (int i = 0; i < contactCount; ++i) {
        char contactFullName[42];  // Combined length of both names with a space
        strcpy(contactFullName, contacts[i].firstName);
        strcat(contactFullName, " ");
        strcat(contactFullName, contacts[i].lastName);

        if (strcmp(contactFullName, fullName) == 0) {
            found = true;
            cout << "ID: " << contacts[i].id << "\n";
            cout << "First Name: " << contacts[i].firstName << "\n";
            cout << "Last Name: " << contacts[i].lastName << "\n";
            cout << "Gender: " << contacts[i].gender << "\n";
            cout << "Phone Number: " << contacts[i].phoneNumber << "\n";
            cout << YELLOW << "------------------------------------\n" << RESET;
        }
    }
    if (!found) {
        cout << "No contact found with the name: " << fullName << "\n";
    }
}

bool isValidName(const char* name) {
    // Check if every character in the name is alphabetic or a space
    for (int i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            return false;
        }
    }
    return true;
}

bool isValidPhoneNumber(const char* phoneNumber) {
    // Check if every character in the phone number is a digit
    for (int i = 0; i < strlen(phoneNumber); i++) {
        if (!isdigit(phoneNumber[i])) {
            return false;
        }
    }
    return true;
}

void addContact(Contact contacts[], int& contactCount, int& nextId) {
    if (contactCount < MAX_CONTACTS) {
        Contact newContact;
        newContact.id = nextId++;

        cout << "Enter First Name: ";
        cin.ignore();
        cin.get(newContact.firstName, sizeof(newContact.firstName));
        while (!isValidName(newContact.firstName)) {
            cout << "Invalid input. Please enter a valid First Name: ";
            cin.ignore();
            cin.get(newContact.firstName, sizeof(newContact.firstName));
        }

        cout << "Enter Last Name: ";
        cin.ignore();
        cin.get(newContact.lastName, sizeof(newContact.lastName));
        while (!isValidName(newContact.lastName)) {
            cout << "Invalid input. Please enter a valid Last Name: ";
            cin.ignore();
            cin.get(newContact.lastName, sizeof(newContact.lastName));
        }

        while (true) {
            cout << "Enter Gender (M/F): ";
            cin >> newContact.gender;
            newContact.gender = toupper(newContact.gender); // Convert to uppercase
            if (newContact.gender == 'M' || newContact.gender == 'F') {
                break;
            }
            cout << "Invalid input. Please enter 'M' for Male or 'F' for Female.\n";
        }

        cout << "Enter Phone Number: ";
        cin >> newContact.phoneNumber;
        while (!isValidPhoneNumber(newContact.phoneNumber)) {
            cout << "Invalid input. Please enter a valid Phone Number: ";
            cin >> newContact.phoneNumber;  
        }

        contacts[contactCount++] = newContact;
    } else {
        cout << "Maximum contacts reached.\n";
    }
}

void modifyContact(Contact contacts[], int contactCount, int id) {
    for (int i = 0; i < contactCount; i++) {
        if (contacts[i].id == id) {
            cout << BLUE << "ID: " << RESET << contacts[i].id << "\n";
            cout << BLUE << "First Name: " << RESET << contacts[i].firstName << "\n";
            cout << BLUE << "Last Name: " << RESET << contacts[i].lastName << "\n";
            cout << BLUE << "Gender: " << RESET << contacts[i].gender << "\n";
            cout << BLUE << "Phone Number: " << RESET << contacts[i].phoneNumber << "\n";
            cout << YELLOW << "------------------------------------\n" << RESET;

            cout << "Choose an action to modify:\n";
            cout << "1. Edit First Name\n";
            cout << "2. Edit Last Name\n";
            cout << "3. Edit Gender\n";
            cout << "4. Edit Phone Number\n";
            cout << "5. Exit\n";
            int choice;
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Enter new First Name: ";
                    cin.ignore();
                    cin.get(contacts[i].firstName, sizeof(contacts[i].firstName));
                    while (!isValidName(contacts[i].firstName)) {
                        cout << "Invalid input. Please enter a valid new First Name: ";
                        cin.ignore();
                        cin.get(contacts[i].firstName, sizeof(contacts[i].firstName));
                    }
                    break;
                case 2:
                    cout << "Enter new Last Name: ";
                    cin.ignore();
                    cin.get(contacts[i].lastName, sizeof(contacts[i].lastName));
                    while (!isValidName(contacts[i].lastName)) {
                        cout << "Invalid input. Please enter a valid new Last Name: ";
                        cin.ignore();
                        cin.get(contacts[i].lastName, sizeof(contacts[i].lastName));
                    }
                    break;
                case 3:
                    while (true) {
                        cout << "Enter new Gender (M/F): ";
                        cin >> contacts[i].gender;
                        contacts[i].gender = toupper(contacts[i].gender); // Convert to uppercase
                        if (contacts[i].gender == 'M' || contacts[i].gender == 'F') {
                            break;
                        }
                        cout << "Invalid input. Please enter 'M' for Male or 'F' for Female.\n";
                    }
                    break;
                case 4:
                    cout << "Enter new Phone Number: ";
                    cin >> contacts[i].phoneNumber;
                    while (!isValidPhoneNumber(contacts[i].phoneNumber)) {
                        cout << "Invalid input. Please enter a valid new Phone Number: ";
                        cin >> contacts[i].phoneNumber;
                    }
                    break;
                case 5:
                    return; // Exit
                default:
                    cout << "Invalid choice.\n";
                    return;
            }
            cout << BLUE << "ID: " << RESET << contacts[i].id << "\n";
            cout << BLUE << "First Name: " << RESET << contacts[i].firstName << "\n";
            cout << BLUE << "Last Name: " << RESET << contacts[i].lastName << "\n";
            cout << BLUE << "Gender: " << RESET << contacts[i].gender << "\n";
            cout << BLUE << "Phone Number: " << RESET << contacts[i].phoneNumber << "\n";
            cout << YELLOW << "------------------------------------\n" << RESET;
            cout << "Contact modified.\n";
            return;
        }
    }
    cout << "No contact found with ID: " << id << "\n";
}

void deleteContact(Contact contacts[], int& contactCount, int id) {
    int foundIndex = -1;
    for (int i = 0; i < contactCount; i++) {
        if (contacts[i].id == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Shift contacts up by one position to fill the gap
        for (int j = foundIndex; j < contactCount - 1; j++) {
            contacts[j] = contacts[j + 1];
            contacts[j].id = j + 1; // Update id to reflect new position
        }
        contactCount--;
        cout << "Contact deleted.\n";
    } else {
        cout << "No contact found with ID: " << id << "\n";
    }
}

void saveContacts(const Contact contacts[], int contactCount, const string& filename) {
    ofstream outFile(filename, ios::binary | ios::trunc);  // Use trunc to overwrite existing file
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }
    for (int i = 0; i < contactCount; i++) {
        outFile.write((char*)(&contacts[i]), sizeof(Contact));
    }
    outFile.close();
}

void loadContacts(Contact contacts[], int& contactCount, int& nextId, const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "Error opening file for reading.\n";
        return;
    }

    contactCount = 0;
    nextId = 1; // Reset nextId before loading contacts

    Contact contact;
    while (inFile.read((char*)(&contact), sizeof(Contact))) {
        contacts[contactCount++] = contact;
        nextId = max(nextId, contact.id + 1);
    }

    inFile.close();
}

int main() {
    ifstream checkFile("contacts.bin", ios::binary);
    if (!checkFile.is_open()) {
        ofstream createFile("contacts.bin", ios::binary);
        if (!createFile) {
            cout << "Error creating file.\n";
            return 1; // Return an error code
        }
        createFile.close(); // Close the newly created file
    } else {
        checkFile.close(); // Close the checked file if it exists
    }

    Contact contacts[MAX_CONTACTS];
    int contactCount = 0;
    int nextId = 1;
    loadContacts(contacts, contactCount, nextId, "contacts.bin");

    char choice;
    while (true) {
        system("CLS");
        cout << GREEN << "Phone Book\n" << RESET;
        cout << "1. List all contacts\n";
        cout << "2. Add a new contact\n";
        cout << "3. Search for a contact\n";
        cout << "4. Modify a contact\n";
        cout << "5. Delete a contact\n";
        cout << "6. Exit\n";
        cout << GREEN << "Enter your choice: " << RESET;
        cin >> choice;

        switch (choice) {
            case '1':
                system("CLS");
                if (contactCount == 0) {
                    cout << RED << "Phonebook is Empty\n" << RESET;
                } else {
                    cout << BLUE << "List of Contacts:\n" << RESET;
                    listContacts(contacts, contactCount);
                }
                break;

            case '2':
                while (true) {
                    system("CLS");
                    addContact(contacts, contactCount, nextId);
                    saveContacts(contacts, contactCount, "contacts.bin");

                    char repeatChoice;
                    cout << "Do you want to add another contact? (y/n): ";
                    cin >> repeatChoice;
                    if (repeatChoice != 'y' && repeatChoice != 'Y') {
                        break;
                    }
                }
                break;

            case '3':
                while (true) {
                    system("CLS");
                    char fullName[42];  // Combined length of both names with a space
                    cout << "Enter full name: ";
                    cin.ignore();
                    cin.get(fullName, sizeof(fullName));
                    while (!isValidName(fullName)) {
                        cout << "Invalid input. Please enter a valid full name: ";
                        cin.ignore();
                        cin.get(fullName, sizeof(fullName));
                    }
                    searchContact(contacts, contactCount, fullName);

                    char repeatChoice;
                    cout << "Do you want to search for another contact? (y/n): ";
                    cin >> repeatChoice;
                    if (repeatChoice != 'y' && repeatChoice != 'Y') {
                        break;
                    }
                }
                break;

            case '4':
                while (true) {
                    system("CLS");
                    int id;
                    cout << "Enter ID of the contact to modify: ";
                    cin >> id;
                    modifyContact(contacts, contactCount, id);
                    saveContacts(contacts, contactCount, "contacts.bin");

                    char repeatChoice;
                    cout << "Do you want to modify another contact? (y/n): ";
                    cin >> repeatChoice;
                    if (repeatChoice != 'y' && repeatChoice != 'Y') {
                        break;
                    }
                }
                break;

            case '5':
                while (true) {
                    system("CLS");
                    int id;
                    cout << "Enter ID of the contact to delete: ";
                    cin >> id;
                    deleteContact(contacts, contactCount, id);
                    saveContacts(contacts, contactCount, "contacts.bin");

                    char repeatChoice;
                    cout << "Do you want to delete another contact? (y/n): ";
                    cin >> repeatChoice;
                    if (repeatChoice != 'y' && repeatChoice != 'Y') {
                        break;
                    }
                }
                break;
            case '6':
                cout << "Exiting...\n";
                break;
            default:
                cout << RED << "Invalid choice.\n" << RESET;
        }

        if (choice != '6') {
            cout << YELLOW << "Press Enter to continue..." << RESET;
            cin.ignore();
            cin.get();
        } else {
            break; // Exit the loop
        }
    }

    return 0;
}
