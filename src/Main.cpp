#include <iostream>
#include "Doctor.cpp"
#include "Appointment.cpp"
#include "FileManager.cpp"
#include "BinarySearch.cpp"
#include "QueryHandler.cpp"
#include "IndexManager.cpp"

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

int main() {
    Doctor d("D008", "Bassem", "123 Main Street");
    Doctor d1("D002", "Hamed", "123 Main Street");
    Doctor d2("D003", "Bassem", "123 Main Street");
    Doctor d3("D004", "Ahmed", "123 Main Street");
    d.addRecord();
    d1.addRecord();
    d3.addRecord();
    d2.addRecord();
    Appointment a("A001", "2021-12-01", "D002");
    Appointment a2("A002", "2021-12-01", "D002");
    Appointment a3("A003", "2021-12-01", "D002");
    a.addAppRecord();
    a2.addAppRecord();
    a3.addAppRecord();



//    ind.insertAppRecordSec("D002", "A001");
    QueryHandler queryHandler;
    cout << "Enter your query: ";
    cin.sync();
    string query;
    getline(cin, query);
    queryHandler.executeQuery(query);

     //    d.deleteRecord("Bassem", "D003");
         BinarySearch s;
         cout << s.searchByDocId("D003");
         cout << s.searchByDocName("Hamed");
        d.printMap();
    /////////////////////////////////////////////
        int cmd;
        cin >> cmd;
        Doctor dIn;
        char id[15], name[30], address[30];
        while (cmd != -1) {
            switch (cmd) {
                case 0:
                    cin >> id >> name >> address;
                    dIn.setID(id);
                    dIn.setName(name);
                    dIn.setAddress(address);
                    dIn.addRecord();
                    break;
                case 1:
                    cin >> id >> name;
                    dIn.deleteRecord(name, id);
                    break;

                default:
                    cout << "Unknown Command";
                    break;
            }
            cout << "enter your command: ";
            cin >> cmd;
        }
    ////////////////////////////////////////////


        Doctor d4("D004", "Dr. Jane", "456 Elm Street");
        d4.addRecord();
//        d4.updatedoc("tone poe", "D004");

    return 0;
}
