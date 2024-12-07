//
// Created by Osama on 27/11/2024.
//
#include <iostream>
#include "IndexManager.h"
#include <vector>
#include <map>

#ifndef HEALTHCARE_MANAGEMENT_SYSTEM_DOCTOR_H
#define HEALTHCARE_MANAGEMENT_SYSTEM_DOCTOR_H
using namespace std;

class Doctor {
private:
    char doctorID[15]{};  // Primary Key
    char name[30]{};
    char address[30]{};
    IndexManager docPrimIndex;
    IndexManager docSecIndex;
    static map<string, int> mp;
    static vector<int> availist;
public:
    Doctor();

    Doctor(const char *id, const char *name, const char *address);

    int readLastLine();

    void setID(const char *id);

    void setName(const char *name);

    void setAddress(const char *address);

    void addRecord();

    void deleteRecord(const string &docName, const string &id);

    static void updateDoc(const char *name, string id);

    void initialize_map(fstream &file);

    void printMap();
};


#endif //HEALTHCARE_MANAGEMENT_SYSTEM_DOCTOR_H
