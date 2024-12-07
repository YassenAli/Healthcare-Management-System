#include <iostream>
#include "Doctor.cpp"
#include "Appointment.h"
#include "FileManager.cpp"
#include "BinarySearch.cpp"
#include "QueryHandler.h"
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
    std::cout << "9. Write a query\n";
    std::cout << "0. Exit\n";
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
    int command;
    Doctor doc;
    char id[15], name[30], address[30];
    Appointment App;
    char appId[15], date[30], docId[30];
    BinarySearch sDoc;
    BinarySearch sApp;
    QueryHandler queryHandler;
    string query;

    displayMenu();
    cin >> command;
    while (command != 0) {
        switch (command) {
            case 1:
                cout << "Enter Doctor Id, Doctor Name, Doctor Address\n";
                cin >> id >> name >> address;
                doc.setID(id);
                doc.setName(name);
                doc.setAddress(address);
                doc.addRecord();
                displayMenu();

                break;
            case 2:
                cout << "Enter Appointment ID , Appointment Date, Doctor Id\n";
                cin >> appId >> date >> docId;
                App.setAppointmentID(appId);
                App.setAppointmentDate(date);
                App.setDocID(docId);
                App.addAppRecord();
                displayMenu();

                break;
            case 3:
                cout << "Enter the record ID you want to update\n";
                cin >> id;
                cout << "Enter new Name\n";
                cin >> name;
                doc.updateDoc(name, id);
                displayMenu();

                break;
            case 4:
                cout << "Enter the record ID you want to update\n";
                cin >> appId;
                cout << "Enter new date\n";
                cin >> date;
                doc.updateDoc(date, appId);
                displayMenu();

                break;
            case 5:
                cout << "Enter the record ID and Name you want to delete\n";
                cin >> id >> name;
                doc.deleteRecord(name, id);
                displayMenu();

                break;

            case 6:
                cout << "Enter the record ID and Date you want to delete\n";
                cin >> appId >> date;
                App.deleteAppRecord(date, appId);
                displayMenu();

                break;
            case 7:
                cout << "Enter the doctor Id\n";
                cin >> id;
                cout << sDoc.searchByDocId(id) << endl;
                displayMenu();

                break;
            case 8:
                cout << "Enter the Appointment Id\n";
                cin >> appId;
                cout << sApp.searchByAppId(appId) << endl;
                displayMenu();

                break;

            case 9:
                cout << "Enter your query: ";
                cin.sync();
                getline(cin, query);
                queryHandler.executeQuery(query);
                displayMenu();

                break;
            case 0:
                return 0;
            default:
                break;
        }
    }
//    Doctor d("D008", "Bassem", "123 Main Street");
//    Doctor d1("D002", "Hamed", "123 Main Street");
//    Doctor d2("D003", "Bassem", "123 Main Street");
//    Doctor d3("D004", "Ahmed", "123 Main Street");
//    d.addRecord();
//    d1.addRecord();
//    d3.addRecord();
//    d2.addRecord();
//    Appointment a("A001", "2021-12-01", "D002");
//    Appointment a2("A002", "2021-12-01", "D002");
//    Appointment a3("A003", "2021-12-01", "D002");
//    a.addAppRecord();
//    a2.addAppRecord();
//    a3.addAppRecord();
//    ind.insertAppRecordSec("D002", "A001");


    // //    d.deleteRecord("Bassem", "D003");
    //     BinarySearch s;
    //     cout << s.searchByDocId("D003");
    //     cout << s.searchByDocName("Hamed");
    //    d.printMap();
    ///////////////////////////////////////////////
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

    //
    //    Doctor d4("D004", "Dr. Jane", "456 Elm Street");
    //    d4.addRecord();
    //    d4.updatedoc("tone poe", "D004");

    return 0;
}
