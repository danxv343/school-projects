#include <iostream>
#include <iomanip>

using namespace std;

// Function to display general information about the fitness center
void displayInformation() {
    cout << "Fitness Center Membership Cost Calculator" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Membership Cost: $100 per month" << endl;
    cout << "Personal Training Session Cost: $50 per session" << endl;
    cout << "Senior Citizens Discount: 30%" << endl;
    cout << "12+ Months Discount: 15%" << endl;
    cout << "5+ Personal Training Sessions Discount: 20% per session" << endl;
    cout << "----------------------------------------" << endl;
}

// Function to get necessary information from the user
void getMembershipInfo(int& months, int& sessions, bool& isSenior) {
    cout << "Enter the number of months you want to join for: ";
    cin >> months;

    cout << "Enter the number of personal training sessions you want to buy: ";
    cin >> sessions;

    cout << "Are you a senior citizen? (1 for yes, 0 for no): ";
    cin >> isSenior;
}

// Function to determine the membership cost
double calculateMembershipCost(int months, int sessions, bool isSenior) {
    double cost = months * 100.0;  // Initial cost based on months

    if (isSenior) {
        cost -= cost * 0.3;  // Apply senior citizens discount
    }

    if (months >= 12) {
        cost -= cost * 0.15;  // Apply 12+ months discount
    }

    double sessionCost = 50.0;  // Cost per session

    if (sessions > 5) {
        double sessionDiscount = sessions * 0.2 * sessionCost;  // Calculate total session discount
        sessionCost -= sessionDiscount / sessions;  // Adjust session cost after applying discount
    }

    cost += sessions * sessionCost;  // Add the cost of personal training sessions to the membership cost

    return cost;
}

int main() {
    displayInformation();

    int months, sessions;
    bool isSenior;

    getMembershipInfo(months, sessions, isSenior);

    double totalCost = calculateMembershipCost(months, sessions, isSenior);

    cout << fixed << setprecision(2);//for the sake of displaying the cost value limited to two decimal points
    cout << "Total Membership Cost: $" << totalCost << endl;

    return 0;
}
