#include <iostream>
#include "IndexManager.h"
#include <vector>
#include <map>

#ifndef HEALTHCARE_MANAGEMENT_SYSTEM_APPOINTMENT_H
#define HEALTHCARE_MANAGEMENT_SYSTEM_APPOINTMENT_H
using namespace std;

class Appointment {
private:
    char appointmentID[15]{};  // Primary Key
    char appointmentDate[30]{};
    char doctorID[30]{};
    static map<string, int> appointmentMap;
    static vector<int> availist;
    static IndexManager AppPrimIndex;
    static IndexManager AppSecIndex;
public:
    Appointment();

    Appointment(const char *appointmentId, const char *date, const char *doctorID);

    int readLastLine();

    void setAppointmentID(const char *appointmentid);

    void setAppointmentDate(const char *date);

    void setDocID(const char *docID);

    void addAppRecord();

    void deleteAppRecord(const string &docId, const string &id);

    void updateAppointmentDate(const char *date, const string &id);

};

#endif
