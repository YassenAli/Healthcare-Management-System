#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Doctor {
public:
    string doctorID;   // Primary Key
    string name;
    string address;

    Doctor(const string &id, const string &name, const string &address)
            : doctorID(id), name(name), address(address) {}

    void saveRecord() {
        ofstream file("data/doctors.txt", ios::app);
        if (file.is_open()) {
            file << doctorID << '|' << name << '|' << address << '\n';
            file.close();
        }
    }

    void deleteRecord(const string &id) {
        // Logic for deleting a doctor (mark with *)
    }
};
