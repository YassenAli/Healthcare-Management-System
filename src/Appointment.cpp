#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Appointment {
public:
    string appointmentID; // Primary Key
    string date;
    string doctorID;      // Secondary Key

    Appointment(const string &id, const string &date, const string &doctorID)
            : appointmentID(id), date(date), doctorID(doctorID) {}

    void saveRecord() {
        ofstream file("data/appointments.txt", ios::app);
        if (file.is_open()) {
            file << appointmentID << '|' << date << '|' << doctorID << '\n';
            file.close();
        }
    }

    void deleteRecord(const string &id) {
        // Logic for deleting an appointment (mark with *)
    }
};
