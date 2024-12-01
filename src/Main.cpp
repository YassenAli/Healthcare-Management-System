#include <iostream>
#include "Doctor.h"
#include "Appointment.cpp"
#include "FileManager.cpp"
#include "IndexManager.h"

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
    Doctor d("D008", "Bassem", "123 Main Street");
    Doctor d1("D002", "Hamed", "123 Main Street");
    Doctor d2("D003", "Bassem", "123 Main Street");
    Doctor d3("D004", "Ahmed", "123 Main Street");
    d.addRecord();
    d1.addRecord();
    d3.addRecord();
    d2.addRecord();
//    d.printMap();
//////////////////////////////////////////////
//    int cmd;
//    cin >> cmd;
//    Doctor dIn;
//    char id[15], name[30], address[30];
//    while (cmd != -1) {
//        switch (cmd) {
//            case 0:
//                cin >> id >> name >> address;
//                dIn.setID(id);
//                dIn.setName(name);
//                dIn.setAddress(address);
//                dIn.addRecord();
//                break;
//            case 1:
//                cin >> id;
//                dIn.deleteRecord(id);
//                break;
//
//            default:
//                cout << "Unknown Command";
//                break;
//        }
//        cout << "enter your command: ";
//        cin >> cmd;
//    }
//////////////////////////////////////////////
//
//    d.deleteRecord("Bassem", "D005");
//
//    Doctor d4("D004", "Dr. Jane", "456 Elm Street");
//    d4.addRecord();
//    d4.updatedoc("tone poe", "D004");

//    IndexManager ind;
//    ind.insertDocRecordSec("osama", "D002");
//    ind.insertDocRecordSec("osama", "D004");
//    ind.insertDocRecordSec("osma", "D001");
//    ind.insertDocRecordSec("osma", "D005");
//    ind.insertDocRecordSec("osama", "D010");
    return 0;
}
