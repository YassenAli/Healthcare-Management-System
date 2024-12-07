#include <iostream>
#include "IndexManager.h"
#include <vector>
#include <map>

#ifndef HEALTHCARE_MANAGEMENT_SYSTEM_DOCTOR_H
#define HEALTHCARE_MANAGEMENT_SYSTEM_DOCTOR_H
using namespace std;

class Doctor {
private:
    char appointmentID[15]{};  // Primary Key
    char appointmentDate[30]{};
    char doctorID[30]{};
    static map<string, int> mp;
    static vector<int> availist;
public:
    Doctor();

    Doctor(const char *appointmentId, const char *date, const char *doctorID);

    void setID(const char *appointmentid);

    void setName(const char *date);

    void setAddress(const char *doctorID);

    void addRecord();

    void deleteRecord(const string &date, const string &id);

    static void updateDoc(const char *date, string id);

    void initialize_map(fstream &file);

    void printMap();
};

