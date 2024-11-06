#include <iostream>
#include "Doctor.cpp"
#include "Appointment.cpp"
#include "FileManager.cpp"

using namesapce std;

void displayMenu() {
    std::cout << "1. Add New Doctor\n";
    std::cout << "2. Add New Appointment\n";
    std::cout << "3. Update Doctor\n";
    std::cout << "4. Update Appointment\n";
    std::cout << "5. Delete Doctor\n";
    std::cout << "6. Delete Appointment\n";
    std::cout << "7. Print Doctor Info\n";
    std::cout << "8. Print Appointment Info\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter choice: ";
}

int main() {
    int choice;
    displayMenu();
    std::cin >> choice;

    FileManager fileManager;
    // Variables for doctor and appointment

    // Logic to handle different menu choices
    switch (choice) {
        case 1:
            // Add new doctor
            break;
        case 2:
            // Add new appointment
            break;
            // Other cases
    }

    return 0;
}
