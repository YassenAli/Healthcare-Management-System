#include <iostream>
#include "Doctor.cpp"
#include "Appointment.cpp"
#include "FileManager.cpp"

using namespace std;

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

/*int main() {
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
}*/
int main() {
    Doctor d("D001", "Dr. John Doe", "123 Main Street");
    Doctor d1("D002", "Dr. John", "123 Main Street");
    Doctor d2("D003", "Dr. Doe", "123 Main Street");
    Doctor d3("D004", "John Doe", "123 Main Street");
    d.addRecord();
    d1.addRecord();
    d2.addRecord();
    d3.addRecord();
    d.deleteRecord("D002");

    Doctor d4("D005", "Dr. Jane ", "456 Elm Street");
    d4.addRecord();
    d4.updatedoc("Dr. Jane Smith", "D005");
    return 0;
}
