//
// Created by Osama on 23/11/2024.
//

#include "IndexManager.h"
#include <bits/stdc++.h>

map<string, int> IndexManager::doctorPrimIndex;
map<string, int> IndexManager::appointmentPrimIndex;
map<string, IndexManager::Node *> IndexManager::doctorSecIndex;
map<string, IndexManager::Node *> IndexManager::appointmentSecIndex;

////////////////////Doctor Primary Indexes////////////////////////////////////////

void IndexManager::insertDocRecord(string const &docId, int recPosition) {
    fstream docIndFile(R"(data/doc_index.txt)",
                       ios::in | ios::out | ios::binary);
    if (!docIndFile.is_open()) {
        cerr << "Failed to open index file.\n";
        return;
    }

    if (doctorPrimIndex.empty() && !isFileEmpty(docIndFile)) {
        initialize_map(docIndFile, doctorPrimIndex);//initializing the map if its empty and the data file isn't empty
    }
    if (recPosition != 0)
        recPosition + 5;
    doctorPrimIndex.insert({docId, recPosition + 4});//insert the new record to the index map
    write_to_file(docIndFile, doctorPrimIndex);//rewriting the index file to be updated

    docIndFile.close();
}

void IndexManager::deleteDocRecord(const string &docId) {
    fstream docIndFile(R"(data/doc_index.txt)",
                       ios::in | ios::out | ios::trunc);
    if (!docIndFile.is_open()) {
        cerr << "Failed to open index file.\n";
        return;
    }

    if (doctorPrimIndex.empty() && !isFileEmpty(docIndFile)) {
        initialize_map(docIndFile, doctorPrimIndex);//initializing the map if its empty and the data file isn't empty
    }
    doctorPrimIndex.erase(docId);//erasing the record from the index map
    write_to_file(docIndFile, doctorPrimIndex);//rewriting the index file
    docIndFile.close();
}

//////////////////Doctor Secondary Indexes////////////////////////////////////////

void IndexManager::insertDocRecordSec(const string &docName, const string &docId) {
    fstream docSecFile(R"(data/doc_sec_index.txt)",
                       ios::in | ios::out);
    if (!docSecFile.is_open()) {
        cerr << "Failed to open index file.\n";
        return;
    }
    if (doctorSecIndex.empty() && !isFileEmpty(docSecFile)) {
        initialize_sec_map(docSecFile, doctorSecIndex);
    }
    if (doctorSecIndex.find(docName) == doctorSecIndex.end()) {
        doctorSecIndex[docName] = new Node(docId);
    } else {
        Node *current = doctorSecIndex[docName];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Node(docId);
    }
    write_to_sec_file(docSecFile, doctorSecIndex);

}

void IndexManager::deleteDocRecordSec(const string &docName, const string &docId) {
    fstream docSecFile(R"(data/doc_sec_index.txt)",
                       ios::in | ios::out | ios::trunc);
    if (!docSecFile.is_open()) {
        cerr << "Failed to open index file.\n";
        return;
    }

    if (doctorSecIndex.empty() && !isFileEmpty(docSecFile)) {
        initialize_sec_map(docSecFile, doctorSecIndex);//initializing the map if its empty and the data file isn't empty
    }
    if (doctorSecIndex.find(docName) == doctorSecIndex.end())return;



//0 1 2 3 4
    Node *head = doctorSecIndex[docName];
    Node *current = head;
    Node *tail = nullptr;

    while (current != nullptr) {
        if (current->primaryKey == docId) {
            if (tail == nullptr) {
                doctorSecIndex[docName] = current->next;

                if (doctorSecIndex[docName] == nullptr)
                    doctorSecIndex.erase(docName);


            } else {
                tail->next = current->next;
            }

            delete current;
            write_to_sec_file(docSecFile, doctorSecIndex);
            docSecFile.close();
            return;
        }
        tail = current;
        current = current->next;
    }
    cerr << "Id is not found";
    write_to_sec_file(docSecFile, doctorSecIndex);
    docSecFile.close();

}

/////////////////////Appointment Primary Indexes//////////////////////////////

void IndexManager::insertAppRecord(string const &appId, int recPosition) {
    fstream appIndFile(R"(data/appointment_index.txt)",
                       ios::in | ios::out | ios::binary);
    if (!appIndFile.is_open()) {
        cerr << "Failed to open index file.\n";
        return;
    }

    if (appointmentPrimIndex.empty() && !isFileEmpty(appIndFile)) {
        initialize_map(appIndFile,
                       appointmentPrimIndex);//initializing the map if its empty and the data file isn't empty
    }
    if (recPosition != 0)
        recPosition + 5;
    appointmentPrimIndex.insert({appId, recPosition + 4});//insert the new record to the index map
    write_to_file(appIndFile, appointmentPrimIndex);//rewriting the index file to be updated

    appIndFile.close();
}

void IndexManager::deleteAppRecord(const string &appId) {
    fstream appIndFile(R"(data/appointment_index.txt)",
                       ios::in | ios::out | ios::trunc);
    if (!appIndFile.is_open()) {
        cerr << "Failed to open index file.\n";
        return;
    }

    if (appointmentPrimIndex.empty() && !isFileEmpty(appIndFile)) {
        initialize_map(appIndFile,
                       appointmentPrimIndex);//initializing the map if its empty and the data file isn't empty
    }
    appointmentPrimIndex.erase(appId);//erasing the record from the index map
    write_to_file(appIndFile, appointmentPrimIndex);//rewriting the index file
    appIndFile.close();
}

////////////////Appointment Secondary Indexes/////////////////////////////////////
void IndexManager::insertAppRecordSec(const string &docId, const string &appId) {
    fstream appSecFile(R"(data/app_sec_index.txt)",
                       ios::in | ios::out);
    if (!appSecFile.is_open()) {
        cerr << "Failed to open index file.\n";
        return;
    }
    if (appointmentSecIndex.empty() && !isFileEmpty(appSecFile)) {
        initialize_sec_map(appSecFile, appointmentSecIndex);
    }
    if (appointmentSecIndex.find(docId) == appointmentSecIndex.end()) {
        doctorSecIndex[docId] = new Node(docId);
    } else {
        Node *current = doctorSecIndex[appId];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Node(docId);
    }
    write_to_sec_file(appSecFile, appointmentSecIndex);
}

void IndexManager::deleteAppRecordSec(const string &docId, const string &appId) {
    fstream appSecFile(R"(data/app_sec_index.txt)",
                       ios::in | ios::out | ios::trunc);
    if (!appSecFile.is_open()) {
        cerr << "Failed to open index file.\n";
        return;
    }

    if (appointmentSecIndex.empty() && !isFileEmpty(appSecFile)) {
        initialize_sec_map(appSecFile, appointmentSecIndex);//initializing the map if its empty and the data file isn't empty
    }
    if (appointmentSecIndex.find(appId) == appointmentSecIndex.end())return;


//0 1 2 3 4
    Node *head = appointmentSecIndex[appId];
    Node *current = head;
    Node *tail = nullptr;

    while (current != nullptr) {
        if (current->primaryKey == appId) {
            if (tail == nullptr) {
                doctorSecIndex[appId] = current->next;

                if (doctorSecIndex[appId] == nullptr)
                    appointmentSecIndex.erase(appId);


            } else {
                tail->next = current->next;
            }

            delete current;
            write_to_sec_file(appSecFile, appointmentSecIndex);
            appSecFile.close();
            return;
        }
        tail = current;
        current = current->next;
    }
    cerr << "Id is not found";
    write_to_sec_file(appSecFile, appointmentSecIndex);
    appSecFile.close();
}

///////////////////////////////////Shared Functions////////////////////////////////////////

//Function to initialize the map if the file has records and the map is empty
void IndexManager::initialize_map(fstream &file, map<string, int> &map) {
    file.seekp(0);

    while (!file.eof()) {
        string line;
        string id;
        string initial_offset;
        getline(file, line, '\n');

        if (line.empty()) {
            continue; // Skip empty lines
        }

        // Extract the ID (first 4 characters)
        id += line[0];
        id += line[1];
        id += line[2];
        id += line[3];

        // Extract the offset (characters after index 4)
        for (int i = 5; i < line.length(); ++i) {
            initial_offset += line[i];
        }

        // Convert `initial_offset` to an integer without using `stoi`
        int offset = 0;
        for (char c : initial_offset) {
            if (isdigit(c)) {
                offset = offset * 10 + (c - '0');
            } else {
                break; // Stop parsing if a non-digit character is encountered
            }
        }

        map.insert({id, offset});
    }
}


//Function to write from map to the index file
void IndexManager::write_to_file(fstream &file, map<string, int> const &map) {
    file.seekp(0, ios::beg);
    for (auto const &i: map) {
        file << i.first << "->" << i.second << endl;
    }
}

void IndexManager::initialize_sec_map(fstream &file, map<string, Node *> &map) {
    file.seekg(0);
    string line;
    while (getline(file, line, '\n')) {
        string name;
        string id;
        int index;


        for (int i = 0; i < line.length() && line[i] != '-'; ++i) {
            name += line[i];
            index = i;

        }


        id += line[index + 3];
        id += line[index + 4];
        id += line[index + 5];
        id += line[index + 6];

        map[name] = new Node(id);
        Node *current = map[name];
        id = "";

        for (int i = index + 8; i < line.length(); ++i) {
            if (line[i] == '|') {
                //add the id to the key name

                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = new Node(id);
                continue;
            }
            id += line[i];

        }
    }
}

void IndexManager::printSecMap(map<string, Node *> &map) {
    Node *current;

    for (auto const &i: map) {
        current = i.second;
        cout << i.first << " -> ";
        while (current != nullptr) {
            cout << current->primaryKey << '|';
            current = current->next;
        }
        cout << endl;
    }
}

void IndexManager::write_to_sec_file(fstream &file, map<string, Node *> const &map) {
    file.seekp(0);
    Node *current;
    for (auto const &i: map) {
        current = i.second;
        file << i.first << " -> ";
        while (current != nullptr) {
            file << current->primaryKey << '|';
            current = current->next;
        }
        file << endl;
    }
}

bool IndexManager::isFileEmpty(fstream &file) {
    file.seekg(0, ios::end);
    return file.tellg() == 0;
}





//#include <iostream>
//#include <fstream>
//#include <string>
//#include <cstring>
//#include <map>
//#include <vector>
//#include "IndexManager.h"
//#include "GlobalDataTypes.cpp"
//
//using namespace std;
//
//
//
//class Doctor {
//private:
//    char doctorID[15]{};  // Primary Key
//    char name[30]{};
//    char address[30]{};
//    IndexManager docIndex;
//
//
//public:
//    Doctor() {
//        strncpy(doctorID, "0", sizeof(doctorID) - 1);
//        strncpy(this->name, "ahmed", sizeof(this->name) - 1);
//        strncpy(this->address, "123 baker street", sizeof(this->address) - 1);
//    }
//
//
//    Doctor(const char *id, const char *name, const char *address) {
//        strncpy(doctorID, id, sizeof(doctorID) - 1);
//        strncpy(this->name, name, sizeof(this->name) - 1);
//        strncpy(this->address, address, sizeof(this->address) - 1);
//    }
//
//    void setID(const char *id) {
//        strncpy(doctorID, id, sizeof(doctorID) - 1);
//    }
//
//    void setName(const char *name) {
//        strncpy(this->name, name, sizeof(this->name) - 1);
//    }
//
//    void setAddress(const char *address) {
//        strncpy(this->address, address, sizeof(this->address) - 1);
//    }
//
//    void addRecord() {
//        int actualLength;
//        fstream file("C:\\Users\\Osama\\Desktop\\Healthcare-Management-System\\data\\doctors.txt",
//                     ios::in | ios::out | ios::binary);
//        if (!file.is_open()) {
//            cerr << "Failed to open the file.\n";
//            return;
//        }
//        if (mp.find(doctorID) != mp.end()) {
//            cerr << "cannot duplicate doctor id\n";
//            return;
//        }
//        int startPos;
//        if (availist.empty()) {
//            file.seekp(0, ios::end);
//            startPos = file.tellp();
//            actualLength = strlen(doctorID) + strlen(name) + strlen(address) + 2;
//            file << " " << actualLength << ' ' << doctorID << '|' << name << '|' << address << '\n';
//
//        } else {
//            startPos = availist.back();
//            availist.pop_back();
//            file.seekp(startPos, ios::beg);
//            actualLength = strlen(doctorID) + strlen(name) + strlen(address) + 2;
//            file << " " << actualLength << ' ' << doctorID << '|' << name << '|' << address << '\n';
//        }
//        docIndex.insertDocRecord(doctorID, startPos + 10);
//        mp[doctorID] = startPos;
//        file.close();
//    }
//
//    void deleteRecord(const string &id) {
//        if (mp.find(id) == mp.end()) {
//            cerr << "Record with ID " << id << " not found.\n";
//            return;
//        }
//        fstream file("C:\\Users\\Osama\\Desktop\\Healthcare-Management-System\\data\\doctors.txt",
//                     ios::in | ios::out | ios::binary);
//        if (file.is_open()) {
//            int pos = mp[id];
//            availist.push_back(pos);
//            file.seekp(pos, ios::beg);
//            file.put('*');
//            mp.erase(id);
//            file.close();
//        } else {
//            cerr << "Failed to open the file for deletion.\n";
//        }
//        docIndex.deleteDocRecord(doctorID);
//        file.close();
//    }
//
////    void updatedoc(const char *name, string id) {
////        fstream file("data/doctors.txt", ios::in | ios::out | ios::binary);
////        if (file.is_open()) {
////            int pos = mp[id];
////            file.seekg(pos, ios::beg);
////            string record;
////            getline(file, record);
////            int a1 = 0, a2 = 0, c = 0;
////            for (int i = 0; i < record.size(); ++i) {
////                if (record[i] == '|') {
////                    c++;
////                    if (c == 1) {
////                        a1 = i + 1;
////                    }
////                    if (c == 2) {
////                        a2 = i;
////                        break;
////                    }
////                }
////            }
////            file.seekp(pos + a1, ios::beg);
////            char m[a2 - a1];
////            memset(m, ' ', a2 - a1);
////            strcpy(m, name);
////            file.write(m, sizeof(m));
////            file.close();
////        } else {
////            cerr << "Failed to open the file for updating.\n";
////        }
////    }
//};