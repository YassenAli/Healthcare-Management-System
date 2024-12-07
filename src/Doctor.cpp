//
// Created by Osama on 27/11/2024.
//

#include "Doctor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <sstream>
#include <filesystem>
#include "IndexManager.h"

map<string, int> Doctor::mp;
using namespace std;

int Doctor::readLastLine() {
    filesystem::path filePath = std::filesystem::current_path() / "data" / "Doctor_Avail_list.txt";
    fstream file;file.open(filePath,ios::in | ios::out | ios::binary);
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
    fstream outFile(filePath,
                  ios :: trunc);
    if (!outFile.is_open()) {
        throw ios_base::failure("Failed to open file for writing");
    }
    outFile << updatedContent;
    outFile.close();

    return stoi(lastLine);
}

Doctor::Doctor() {
    strncpy(doctorID, "0", sizeof(doctorID) - 1);
    strncpy(this->name, "ahmed", sizeof(this->name) - 1);
    strncpy(this->address, "123 baker street", sizeof(this->address) - 1);
}


Doctor::Doctor(const char *id, const char *name, const char *address) {
    strncpy(doctorID, id, sizeof(doctorID) - 1);
    strncpy(this->name, name, sizeof(this->name) - 1);
    strncpy(this->address, address, sizeof(this->address) - 1);
}

void Doctor::setID(const char *id) {
    strncpy(doctorID, id, sizeof(doctorID) - 1);
}

void Doctor::setName(const char *name) {
    strncpy(this->name, name, sizeof(this->name) - 1);
}

void Doctor::setAddress(const char *address) {
    strncpy(this->address, address, sizeof(this->address) - 1);
}

void Doctor::addRecord() {
    int actualLength;
    filesystem::path filePath = std::filesystem::current_path() / "data" / "doctors.txt";
    fstream file;file.open(filePath,ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cerr << "Failed to open the file.\n";
        return;
    }
//    if (mp.empty() && !file.eof()) {
//        initialize_map(file);
//    }
    if (mp.find(doctorID) != mp.end()) {
        cerr << "cannot duplicate doctor id\n";
        return;
    }
    int startPos = readLastLine();
    if (startPos == -1) {
        file.seekp(0, ios::end);
        startPos = file.tellp();
        actualLength = strlen(doctorID) + strlen(name) + strlen(address) + 2;
        file << " " << actualLength << ' ' << doctorID << '|' << name << '|' << address << '\n';

    } else {
        file.seekp(startPos, ios::beg);
        actualLength = strlen(doctorID) + strlen(name) + strlen(address) + 2;
        file << " " << actualLength << ' ' << doctorID << '|' << name << '|' << address << '\n';
    }
    docPrimIndex.insertDocRecord(doctorID, startPos);
    docSecIndex.insertDocRecordSec(name, doctorID);
    mp[doctorID] = startPos;
    file.close();
}

void Doctor::deleteRecord(const string &docName, const string &id) {

    if (mp.find(id) == mp.end()) {
        cerr << "Record with ID " << id << " not found.\n";
        return;
    }
    filesystem::path filePath = std::filesystem::current_path() / "data" / "doctors.txt";
    fstream file(filePath,
                 ios::in | ios::out | ios::binary);
    filesystem::path filePath1 = std::filesystem::current_path() / "data" / "Doctor_Avail_list.txt";
    fstream file1;file1.open(filePath1, std::ios::in | std::ios::ate | ios::out | ios::app);
    if (file.is_open()) {
        int pos = mp[id];
        file1 << "|" << pos;
        file.seekp(pos, ios::beg);
        file.put('*');
        mp.erase(id);
        file.close();
    } else {
        cerr << "Failed to open the file for deletion.\n";
    }
    docPrimIndex.deleteDocRecord(id);
    docSecIndex.deleteDocRecordSec(docName, id);
    file.close();
}

void Doctor::updateDoc(const char *name, string id) {
    filesystem::path filePath = std::filesystem::current_path() / "data" / "doctors.txt";
    fstream file;file.open(filePath,ios::in | ios::out | ios::binary);
    if (file.is_open()) {
        int pos = mp[id];
        file.seekg(pos, ios::beg);
        string record;
        getline(file, record);
        int a1 = 0, a2 = 0, c = 0;
        for (int i = 0; i < record.size(); ++i) {
            if (record[i] == '|') {
                c++;
                if (c == 1) {
                    a1 = i + 1;
                }
                if (c == 2) {
                    a2 = i;
                    break;
                }
            }
        }
        file.seekp(pos + a1, ios::beg);
        char m[a2 - a1];
        memset(m, ' ', a2 - a1);
        strcpy(m, name);
        file.write(m, sizeof(m));
        file.close();
    } else {
        cerr << "Failed to open the file for updating.\n";
    }
}

void Doctor::printMap() {
    for (auto const &i: mp) {
        cout << i.first << " " << i.second << endl;
    }
}

void Doctor::initialize_map(
        fstream &file) {//Function to initialize the map if the file has records and the map is empty
    file.seekp(0);
    while (!file.eof()) {
        string line;
        string id;
        string initial_offset;
        getline(file, line, '\n');
        id += line[5];
        id += line[6];
        id += line[7];
        id += line[8];

        for (int i = 5; i < line.length(); ++i) {
            initial_offset += line[i];
        }
        int offset = stoi(initial_offset);
        mp.insert({id, offset});
    }

}
