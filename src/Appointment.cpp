#include "Appointment.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <sstream>

using namespace std;
map<string, int> Appointment::appointmentMap;

int Appointment::readLastLine() {
    string filename = "data/Appointment_Avail_list.txt";
    fstream file(filename, std::ios::in | std::ios::ate | ios::out);

//    filesystem::path filePath = std::filesystem::current_path() / "data" / "Appointment_Avail_list.txt";
//    fstream file;file.open(filePath,ios::in | ios::out | ios::binary);

    if (!file.is_open()) {
        throw ios_base::failure("Failed to open file");
    }
    streamoff fileSize = file.tellg();
    if (fileSize == 0) {
        return -1;
    }
    file.seekg(0, ios::beg);
    ostringstream buffer;
    buffer << file.rdbuf();
    file.close();
    string content = buffer.str();
    size_t lastNewline = content.find_last_of('|');

    string lastLine;
    string updatedContent;
    if (lastNewline == string::npos) {
        lastLine = content;
        updatedContent = "";
    } else {
        lastLine = content.substr(lastNewline + 1);
        updatedContent = content.substr(0, lastNewline);
    }
    file.open(filename,ios::in | ios::out | ios::binary | ios :: trunc);
    if (!file.is_open()) {
        throw ios_base::failure("Failed to open file for writing");
    }
    file << updatedContent;
    file.close();

    // Extract the integer part from lastLine
    std::istringstream iss(lastLine);
    int extractedNumber;
    if (!(iss >> extractedNumber)) {
        return -1; // Return -1 if no valid integer found
    }

    return extractedNumber; // Return the extracted integer
}


// Constructors
Appointment::Appointment() {
    strncpy(appointmentID, "0", sizeof(appointmentID) - 1);
    strncpy(appointmentDate, "", sizeof(appointmentDate) - 1);
    strncpy(doctorID, "", sizeof(doctorID) - 1);
}

Appointment::Appointment(const char *id, const char *date, const char *docID) {
    strncpy(appointmentID, id, sizeof(appointmentID) - 1);
    strncpy(appointmentDate, date, sizeof(appointmentDate) - 1);
    strncpy(doctorID, docID, sizeof(doctorID) - 1);
}

// Setters

void Appointment::setAppointmentID(const char *appointmentid) {
    strncpy(appointmentID, appointmentid, sizeof(appointmentID) - 1);
}

void Appointment::setAppointmentDate(const char *date) {
    strncpy(appointmentDate, date, sizeof(appointmentDate) - 1);
}

void Appointment::setDocID(const char *docID) {
    strncpy(doctorID, docID, sizeof(doctorID) - 1);
}

// Add Record
void Appointment::addAppRecord() {
    int actualLength;

    fstream file(R"(data/appointments.txt)", ios::in | ios::out | ios::binary | ios::app);

//    filesystem::path filePath = std::filesystem::current_path() / "data" / "doctors.txt";
//    fstream file;file.open(filePath,ios::in | ios::out | ios::binary);

    if (!file.is_open()) {
        cerr << "Failed to open the file.\n";
        return;
    }

    if (appointmentMap.find(appointmentID) != appointmentMap.end()) {
        cerr << "Cannot duplicate appointment ID.\n";
        return;
    }

    int startPos = readLastLine();
    if (startPos == -1) {
        file.seekp(0, ios::end);
        startPos = file.tellp();
        actualLength = strlen(appointmentID) + strlen(appointmentDate) + strlen(doctorID) + 2;
        file << " " << actualLength << ' ' << appointmentID << '|' << appointmentDate << '|' << doctorID << '\n';

    } else {
        file.seekp(startPos, ios::beg);
        actualLength = strlen(appointmentID) + strlen(appointmentDate) + strlen(doctorID) + 2;
        file << " " << actualLength << ' ' << appointmentID << '|' << appointmentDate << '|' << doctorID << '\n';
    }

    appointmentMap[appointmentID] = startPos;
    AppPrimIndex.insertAppRecord(appointmentID, startPos);
    AppSecIndex.insertAppRecordSec(doctorID, appointmentID);
    file.close();
}


void Appointment::deleteAppRecord(const string &docId, const string &appId) {
    if (appointmentMap.find(appId) == appointmentMap.end()) {
        cerr << "Record with ID " << appId << " not found.\n";
        return;
    }

    fstream file(R"(data/appointments.txt)", ios::in | ios::out | ios::binary);

//    filesystem::path filePath = std::filesystem::current_path() / "data" / "doctors.txt";
//    fstream file;file.open(filePath,ios::in | ios::out | ios::binary);

    if (!file.is_open()) {
        cerr << "Failed to open the file for deletion.\n";
        return;
    }
//    filesystem::path filePath1 = filesystem::current_path() / "data" / "Appointment_Avail_list.txt";
//    fstream file1;file1.open(filePath1,ios::in | ios::out | ios::binary | ios :: app);
    int pos = appointmentMap[appId];
    file << "|" << pos;
    file.seekp(pos, ios::beg);
    file.put('*');
    appointmentMap.erase(appId);
    AppPrimIndex.deleteAppRecord(appId);
    AppSecIndex.deleteAppRecordSec(docId, appId);
    file.close();
}


void Appointment::updateAppointmentDate(const char *date, const string &id) {
    if (appointmentMap.find(id) == appointmentMap.end()) {
        cerr << "Record with ID " << id << " not found.\n";
        return;
    }

    fstream file(R"(data/appointments.txt)", ios::in | ios::out | ios::binary);

//    filesystem::path filePath = std::filesystem::current_path() / "data" / "doctors.txt";
//    fstream file;file.open(filePath,ios::in | ios::out | ios::binary);

    if (!file.is_open()) {
        cerr << "Failed to open the file for updating.\n";
        return;
    }

    int pos = appointmentMap[id];
    file.seekg(pos, ios::beg);
    string record;
    getline(file, record);

    int a1 = 0, a2 = 0, c = 0;
    for (int i = 0; i < record.size(); ++i) {
        if (record[i] == '|') {
            c++;
            if (c == 1) {
                a1 = i + 1;
            } else if (c == 2) {
                a2 = i;
                break;
            }
        }
    }

    file.seekp(pos + a1, ios::beg);
    char m[a2 - a1];
    memset(m, ' ', a2 - a1);
    strncpy(m, date, sizeof(m) - 1);
    file.write(m, sizeof(m));
    file.close();
}