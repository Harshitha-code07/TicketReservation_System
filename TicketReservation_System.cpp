#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Passenger {
    string name;
    int age;
    string category;
    int seatNumber;
};

vector<Passenger> bookedSeats;
vector<Passenger> waitingList;

int seatCounter = 1;

string getCategory(int age, bool disabled) {
    if (disabled) return "Disabled";
    else if (age >= 60) return "Senior";
    else return "Normal";
}

void bookTicket() {
    if (bookedSeats.size() + waitingList.size() >= 10) {
        cout << "No more tickets can be booked. Full.\n";
        return;
    }

    Passenger p;
    char isDisabled;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin,p.name);
    cout << "Enter Age: ";
    cin >> p.age;
    cout << "Are you disabled? (y/n): ";
    cin >> isDisabled;

    p.category = getCategory(p.age, isDisabled == 'y' || isDisabled == 'Y');

    if (bookedSeats.size() < 5) {
        p.seatNumber = seatCounter++;
        bookedSeats.push_back(p);
        cout << "Ticket Booked! Seat No: " << p.seatNumber << endl;
    } else {
        p.seatNumber = -1;
        waitingList.push_back(p);
        cout << "Added to waiting list.\n";
    }

    if (bookedSeats.size() + waitingList.size() == 10) {
        // Assign 3 from waiting list to bookedSeats based on priority
        int assigned = 0;
        while (assigned < 3 && !waitingList.empty()) {
            int priorityIndex = -1;
            string bestCategory = "Normal";

            for (int i = 0; i < waitingList.size(); i++) {
                if (waitingList[i].category == "Disabled") {
                    priorityIndex = i;
                    bestCategory = "Disabled";
                    break;
                } else if (waitingList[i].category == "Senior" && bestCategory != "Disabled") {
                    priorityIndex = i;
                    bestCategory = "Senior";
                } else if (waitingList[i].category == "Normal" && bestCategory == "Normal" && priorityIndex == -1) {
                    priorityIndex = i;
                }
            }

            if (priorityIndex != -1) {
                waitingList[priorityIndex].seatNumber = seatCounter++;
                bookedSeats.push_back(waitingList[priorityIndex]);
                cout << "Priority Ticket Confirmed: " << waitingList[priorityIndex].name << endl;
                waitingList.erase(waitingList.begin() + priorityIndex);
                assigned++;
            }
        }
    }
}

void cancelTicket() {
    int seatNo;
    cout << "Enter Seat Number to Cancel: ";
    cin >> seatNo;

    bool found = false;

    for (int i = 0; i < bookedSeats.size(); i++) {
        if (bookedSeats[i].seatNumber == seatNo) {
            cout << "Cancelled ticket for: " << bookedSeats[i].name << endl;
            bookedSeats.erase(bookedSeats.begin() + i);
            found = true;

            // Assign highest priority from waiting list
            if (!waitingList.empty()) {
                int priorityIndex = -1;
                string bestCategory = "Normal";

                for (int j = 0; j < waitingList.size(); j++) {
                    if (waitingList[j].category == "Disabled") {
                        priorityIndex = j;
                        bestCategory = "Disabled";
                        break;
                    } else if (waitingList[j].category == "Senior" && bestCategory != "Disabled") {
                        priorityIndex = j;
                        bestCategory = "Senior";
                    } else if (waitingList[j].category == "Normal" && bestCategory == "Normal" && priorityIndex == -1) {
                        priorityIndex = j;
                    }
                }

                if (priorityIndex != -1) {
                    waitingList[priorityIndex].seatNumber = seatNo;
                    bookedSeats.push_back(waitingList[priorityIndex]);
                    cout << "Seat Reassigned to: " << waitingList[priorityIndex].name << endl;
                    waitingList.erase(waitingList.begin() + priorityIndex);
                }
            }
            break;
        }
    }

    if (!found) {
        cout << "Seat number not found.\n";
    }
}

void displayBookedTickets() {
    cout << "\n--- Booked Tickets ---\n";
    for (Passenger p : bookedSeats) {
        cout << "Seat " << p.seatNumber << " - " << p.name << " (" << p.category << ", Age " << p.age << ")\n";
    }

    cout << "\n--- Waiting List ---\n";
    for (Passenger p : waitingList) {
        cout << p.name << " (" << p.category << ", Age " << p.age << ")\n";
    }
}

void displayConfirmedTickets() {
    if (bookedSeats.size() + waitingList.size() < 10) {
        cout << "Confirmation view only available after full booking.\n";
        return;
    }

    cout << "\n--- Confirmed Tickets (5 normal + 3 priority from waiting list) ---\n";
    for (int i = 0; i < bookedSeats.size(); i++) {
        if (i < 8) {
            Passenger p = bookedSeats[i];
            cout << "Seat " << p.seatNumber << " - " << p.name << " (" << p.category << ", Age " << p.age << ")\n";
        }
    }
}

int main() {
    int choice;

    do {
        cout << "\n===== Ticket Reservation Menu =====\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. Display Booked Tickets\n";
        cout << "4. Display Confirmed Tickets\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bookTicket();
            break;
        case 2:
            cancelTicket();
            break;
        case 3:
            displayBookedTickets();
            break;
        case 4:
            displayConfirmedTickets();
            break;
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
