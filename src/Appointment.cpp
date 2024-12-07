#include "Doctor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

using namespace std;
map<string, int> Appointment::appointmentMap;
int readLastLine(){
    string filename = "../data/Appointment_Avail_list.txt";
    fstream file(filename, std::ios::in | std::ios::ate | ios :: out);
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
    ofstream outFile(filename, ios::trunc);
    if (!outFile.is_open()) {
        throw ios_base::failure("Failed to open file for writing");
    }
    outFile << updatedContent;
    outFile.close();

    return stoi(lastLine);
}
class Appointment {
private:
    char appointmentID[15]; 
    char appointmentDate[30];
    char doctorID[15];      
    static map<string, int> appointmentMap; 

public:
    // Constructors
    Appointment() {
        strncpy(appointmentID, "0", sizeof(appointmentID) - 1);
        strncpy(appointmentDate, "", sizeof(appointmentDate) - 1);
        strncpy(doctorID, "", sizeof(doctorID) - 1);
    }

    Appointment(const char *id, const char *date, const char *docID) {
        strncpy(appointmentID, id, sizeof(appointmentID) - 1);
        strncpy(appointmentDate, date, sizeof(appointmentDate) - 1);
        strncpy(doctorID, docID, sizeof(doctorID) - 1);
    }

    // Setters
    void setAppointmentID(const char *id) {
        strncpy(appointmentID, id, sizeof(appointmentID) - 1);
    }

    void setAppointmentDate(const char *date) {
        strncpy(appointmentDate, date, sizeof(appointmentDate) - 1);
    }

    void setDoctorID(const char *docID) {
        strncpy(doctorID, docID, sizeof(doctorID) - 1);
    }

    // Add Record
    void addRecord() {
        fstream file(R"(../data/appointments.txt)", ios::in | ios::out | ios::binary | ios::app);
        if (!file.is_open()) {
            cerr << "Failed to open the file.\n";
            return;
        }

        if (appointmentMap.find(appointmentID) != appointmentMap.end()) {
            cerr << "Cannot duplicate appointment ID.\n";
            return;
        }

        int actualLength = strlen(appointmentID) + strlen(appointmentDate) + strlen(doctorID) + 2;
        
        int startPos = file.tellp();

        file << " " << actualLength << ' ' << appointmentID << '|' << appointmentDate << '|' << doctorID << '\n';

        appointmentMap[appointmentID] = startPos;
        file.close();
    }

    
    void deleteRecord(const string &id) {
        if (appointmentMap.find(id) == appointmentMap.end()) {
            cerr << "Record with ID " << id << " not found.\n";
            return;
        }

        fstream file(R"(../data/appointments.txt)", ios::in | ios::out | ios::binary);
        if (!file.is_open()) {
            cerr << "Failed to open the file for deletion.\n";
            return;
        }

        int pos = appointmentMap[id];
        file.seekp(pos, ios::beg);
        file.put('*');
        appointmentMap.erase(id);
        file.close();
    }


    void updateAppointmentDate(const char *date, const string &id) {
        if (appointmentMap.find(id) == appointmentMap.end()) {
            cerr << "Record with ID " << id << " not found.\n";
            return;
        }

        fstream file(R"(../data/appointments.txt)", ios::in | ios::out | ios::binary);
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
};

