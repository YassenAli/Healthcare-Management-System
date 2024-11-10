#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

map<string, int> mp;
vector<int> availist;

class Doctor {
private:
    char doctorID[15];  // Primary Key
    char name[30];
    char address[30];

public:
    Doctor(const char* id, const char* name, const char* address) {
        strncpy(doctorID, id, sizeof(doctorID) - 1);
        strncpy(this->name, name, sizeof(this->name) - 1);
        strncpy(this->address, address, sizeof(this->address) - 1);
    }

    void addRecord() {
        fstream file("data/doctors.txt", ios::in | ios::out | ios::binary);
        if (!file.is_open()) {
            cerr << "Failed to open the file.\n";
            return;
        }

        int startPos;
        if (availist.empty()) {
            file.seekp(0, ios::end);
            startPos = file.tellp();
            int actualLength = strlen(doctorID) + strlen(name) + strlen(address) + 2;
            file << " " << actualLength << ' ' << doctorID << '|' << name << '|' << address << '\n';

        } else {
            startPos = availist.back();
            availist.pop_back();
            file.seekp(startPos, ios::beg);
            int actualLength = strlen(doctorID) + strlen(name) + strlen(address) + 2;
            file << " " << actualLength << ' ' << doctorID << '|' << name << '|' << address << '\n' ;
        }
        mp[doctorID] = startPos;
        file.close();
    }

    void deleteRecord(const string& id) {
        if (mp.find(id) == mp.end()) {
            cerr << "Record with ID " << id << " not found.\n";
            return;
        }
        fstream file("data/doctors.txt", ios::in | ios::out | ios::binary);
        if (file.is_open()) {
            int pos = mp[id];
            availist.push_back(pos);
            file.seekp(pos, ios::beg);
            file.put('*');
            mp.erase(id);
            file.close();
        } else {
            cerr << "Failed to open the file for deletion.\n";
        }
    }

    void updatedoc(const char *name, string id){
        fstream file("data/doctors.txt", ios::in | ios::out | ios::binary);
        if (file.is_open()) {
            int pos = mp[id];
            file.seekg(pos, ios::beg);
            string record;
            getline(file, record);
            int a1=0,a2=0,c=0;
            for (int i = 0; i < record.size(); ++i) {
                if(record[i] == '|'){
                    c++;
                    if(c==1){
                        a1=i+1;
                    }
                    if(c==2){
                        a2=i;
                        break;
                    }
                }
            }
            file.seekp(pos+a1,ios::beg);
            char  m[a2-a1];
            memset(m, ' ', a2-a1);
            strcpy(m,name);
            file.write(m, sizeof(m));
            file.close();
        } else {
            cerr << "Failed to open the file for updating.\n";
        }
    }
};