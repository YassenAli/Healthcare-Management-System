#include "Doctor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <sstream>

#include <algorithm>

#include <filesystem>

#include "IndexManager.h"

map<string, int> Doctor::mp;
using namespace std;

bool isNumeric(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

int Doctor::readLastLine() {

    string filename = "data/Doctor_Avail_list.txt";
    fstream file(filename, std::ios::in | std::ios::ate | ios::out);

//    filesystem::path filePath = std::filesystem::current_path() / "data" / "Doctor_Avail_list.txt";
//    fstream file;file.open(filePath,ios::in | ios::out | ios::binary);

    if (!file.is_open()) {
        throw ios_base::failure("Failed to open file. Line 22");
    }
    streamoff fileSize = file.tellg();
    if (fileSize == 0) {
        return -1; // File is empty
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


    // Open file to update content (truncate)
    ofstream outFile(filename, ios::trunc);

//    fstream outFile(filename,
//                  ios :: trunc);

    if (!outFile.is_open()) {
        throw ios_base::failure("Failed to open file for writing");
    }
    outFile << updatedContent;
    outFile.close();

    // Extract the integer part from lastLine
    std::istringstream iss(lastLine);
    int extractedNumber;
    if (!(iss >> extractedNumber)) {
        return -1; // Return -1 if no valid integer found
    }

    return extractedNumber; // Return the extracted integer
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

    string filename = "data/Doctor_Avail_list.txt";
    fstream file(filename, std::ios::in | std::ios::ate | ios :: out | ios :: app);

//    filesystem::path filePath = std::filesystem::current_path() / "data" / "doctors.txt";
//    fstream file;file.open(filePath,ios::in | ios::out | ios::binary);

    if (!file.is_open()) {
//        cout<<file.fail();
        cerr << "Failed to open the file. Line 84\n";
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

    fstream file(R"(data/doctors.txt)",
                 ios::in | ios::out | ios::binary);
    string filename = "data/Doctor_Avail_list.txt";
//    fstream file1(filename, std::ios::in | std::ios::ate | ios::out | ios::app);

//    filesystem::path filePath = std::filesystem::current_path() / "data" / "doctors.txt";
//    fstream file(filePath,
//                 ios::in | ios::out | ios::binary);
//    filesystem::path filePath1 = std::filesystem::current_path() / "data" / "Doctor_Avail_list.txt";
//    fstream file1;file1.open(filePath1, std::ios::in | std::ios::ate | ios::out | ios::app);

    if (file.is_open()) {
        int pos = mp[id];
        file << "|" << pos;
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

    fstream file(R"(data/doctors.txt)",
                 ios::in | ios::out | ios::binary);

//    filesystem::path filePath = std::filesystem::current_path() / "data" / "doctors.txt";
//    fstream file;file.open(filePath,ios::in | ios::out | ios::binary);

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
        // Convert `initial_offset` to an integer without using `stoi`
        int offset = 0;
        for (char c : initial_offset) {
            if (isdigit(c)) {
                offset = offset * 10 + (c - '0');
            } else {
                break; // Stop parsing if a non-digit character is encountered
            }
        }

        mp.insert({id, offset});
    }
}
