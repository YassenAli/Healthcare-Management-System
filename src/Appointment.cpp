#include <iostream>
#include <fstream>
#include <string>
#include "IndexManager.h"

using namespace std;

class Appointment {
public:
    string appointmentID; // Primary Key
    string date;
    string doctorID;      // Secondary Key
    IndexManager appPrimaryIndex;
    IndexManager appSecondaryIndex;

    Appointment(const string &id, const string &date, const string &doctorID)
            : appointmentID(id), date(date), doctorID(doctorID) {}

    void saveRecord() {
        ofstream file("../data/appointments.txt", ios::app);
        if (file.is_open()) {
            file << appointmentID << '|' << date << '|' << doctorID << '\n';
            file.close();
        }
    }

    void deleteRecord(const string &docId, const string &appId) {
        // Logic for deleting an appointment (mark with *)
        appPrimaryIndex.deleteAppRecord(appId);
        appSecondaryIndex.deleteAppRecordSec(docId, appId);

    }
};
