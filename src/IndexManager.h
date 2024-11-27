//
// Created by Osama on 23/11/2024.
//
#ifndef HEALTHCARE_MANAGEMENT_SYSTEM_INDEXMANAGER_H
#define HEALTHCARE_MANAGEMENT_SYSTEM_INDEXMANAGER_H

#include <vector>
#include <map>
#include <iostream>


using namespace std;

class IndexManager {
private:
    static map<string, int> doctorPrimIndex;
    static map<string, int> appointmentPrimIndex;

    struct Node {
        string primaryKey;
        Node *next;

        Node(const string &key) {
            primaryKey = key;
            next = nullptr;
        }
    };

    static map<string, Node *> doctorSecIndex;
    static map<string, Node *> appointmentSecIndex;

public:

    ////////////////////Doctor Primary Index///////////////////////////
    static void insertDocRecord(string const &docId, int recPosition);

    static void deleteDocRecord(string const &docId);

    ////////////////////Appointment Primary Indexes//////////////////////
    static void insertAppRecord(string const &appId, int recPosition);

    static void deleteAppRecord(const string &appId);

    //////////////////////////Doctor Secondary Index/////////////////////
    static void insertDocRecordSec(string const &docName, string const &docId);

    static void deleteDocRecordSec(const string &docName, const string &docId);

    //////////////////////////Appointment Secondary Index/////////////////////
    static void insertAppRecordSec(const string &docId, const string &appId);

    static void deleteAppRecordSec(const string &docId, const string &appId);

    //////////////////////////Shared Functions/////////////////////
    static void initialize_map(fstream &file, map<string, int> &map);

    static void write_to_file(fstream &file, map<string, int> const &map);

    static bool isFileEmpty(fstream &file);

    static void printSecMap(map<string, Node *> &map);

    static void initialize_sec_map(fstream &file, map<string, Node *> &map);

    static void write_to_sec_file(fstream &file, map<string, Node *> const &map);


};


#endif //HEALTHCARE_MANAGEMENT_SYSTEM_INDEXMANAGER_H
