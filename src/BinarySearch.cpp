#pragma once
#include <bits/stdc++.h>

using namespace std;

struct PersonNode
{
    string name;
    vector<string> ids;
    PersonNode *next;

    PersonNode(const string &name) : name(name), next(nullptr) {}
};

///////////////////////////////////////////////////////////////////////////////////

class BinarySearch
{
private:
    vector<pair<string, string>> primary_doc_index;
    vector<pair<string, string>> primary_app_index;

public:
    //////////////////////Search by Doctor Id/////////////////////////////////
    string searchByDocId(const string &target)
    {
        readPrim("data/doc_index.txt", primary_doc_index);
        int first = 0;
        int last = primary_doc_index.size() - 1;
        int mid;

        while (first <= last)
        {
            mid = (first + last) / 2;

            if (primary_doc_index[mid].first == target)
            {
                return "The offset of " + primary_doc_index[mid].first + " is " + primary_doc_index[mid].second + "\n";
            }
            else if (primary_doc_index[mid].first > target)
            {
                last = mid - 1;
            }
            else
            {
                first = mid + 1;
            }
        }

        return "ID not found.\n";
    }

    /////////////////////Search by Appointment ID////////////////////////////
    string searchByAppId(const string &target)
    {
        readPrim("data/appointment_index.txt", primary_app_index);
        int first = 0;
        int last = primary_app_index.size() - 1;
        int mid;

        while (first <= last)
        {
            mid = (first + last) / 2;

            if (primary_app_index[mid].first == target)
            {
                return "The offset of " + primary_app_index[mid].first + " is " + primary_app_index[mid].second + "\n";
            }
            else if (primary_app_index[mid].first > target)
            {
                last = mid - 1;
            }
            else
            {
                first = mid + 1;
            }
        }

        return "ID not found.\n";
    }

    ////////////////Search IDS by Doctor Name////////////////////////////////
    string searchByDocName(const string &DoctorName)
    {
        PersonNode *head = nullptr;
        readFileToLinkedList("data/doc_sec_index.txt", head);

        vector<PersonNode *> vec = convertLinkedListToVector(head);
        PersonNode *personNode = binarySearchByName(vec, DoctorName);
        if (!personNode)
        {
            return "Name not found.\n";
        }
        vector<string> ids = personNode->ids;
        string result = "Offsets for " + DoctorName + ":\n";
        for (const string &id : ids)
        {
            result += searchByDocId(id);
        }
        return result;
    }

    ////////////////Search Appointments by Doctor ID////////////////////////
    string searchAppByDocId(const string &DocID)
    {
        PersonNode *head = nullptr;
        readFileToLinkedList("data/app_sec_index.txt", head);

        vector<PersonNode *> vec = convertLinkedListToVector(head);
        PersonNode *personNode = binarySearchByName(vec, DocID);
        if (!personNode)
        {
            return "Name not found.\n";
        }
        vector<string> ids = personNode->ids;
        string result = "Offsets for " + DocID + ":\n";
        for (const string &id : ids)
        {
            result += searchByAppId(id);
        }
        return result;
    }

    /////////////////////////////Shared Functions///////////////////////////

    // read doc_index.txt
    static void readPrim(const string &filePath, vector<pair<string, string>> &primary_index)
    {
        fstream file(filePath, ios::in);
        string line;
        if (!file.is_open())
        {
            cerr << "Error opening file." << endl;
            return;
        }
        while (getline(file, line))
        {
            stringstream ss(line);
            string id;
            string value;
            size_t pos = line.find("->");
            if (pos != string::npos)
            {
                id = line.substr(0, 4);
                value = line.substr(6); // Skip the "->" part
                primary_index.push_back(make_pair(id, value));
            }
            else
            {
                cout << "Line format incorrect: " << line << " (No '->' found)" << endl;
            }
        }
        file.close();
    }

    //  read the file(doc_sec_index into a linked list)
    static void readFileToLinkedList(const string &filePath, PersonNode *&head)
    {
        ifstream file(filePath);
        if (!file.is_open())
        {
            cerr << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string name, id_str;
            vector<string> ids;
            if (getline(ss, name, ' '))
            {
                if (getline(ss, id_str))
                {
                    size_t pos = id_str.find("->");
                    if (pos != string::npos)
                    {
                        id_str = id_str.substr(pos + 3); // escape -> and space
                    }
                    stringstream id_stream(id_str);
                    string id;
                    while (getline(id_stream, id, '|'))
                    {
                        if (!id.empty())
                        {
                            ids.push_back(id);
                        }
                    }
                }
            }
            PersonNode *newNode = new PersonNode(name);
            newNode->ids = ids;
            if (head == nullptr)
            {
                head = newNode;
            }
            else
            {
                PersonNode *temp = head;
                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }

        file.close();
    }

    static vector<PersonNode *> convertLinkedListToVector(PersonNode *head)
    {
        vector<PersonNode *> vec;
        PersonNode *temp = head;
        while (temp != nullptr)
        {
            vec.push_back(temp); // Add the PersonNode object to the vector
            temp = temp->next;
        }
        return vec;
    }

    static PersonNode *binarySearchByName(vector<PersonNode *> &vec, const string &target)
    {
        int first = 0;
        int last = vec.size() - 1;
        int mid;

        while (first <= last)
        {
            mid = (first + last) / 2;

            if (vec[mid]->name == target)
            {
                return vec[mid];
            }
            else if (vec[mid]->name < target)
            {
                first = mid + 1;
            }
            else
            {
                last = mid - 1;
            }
        }

        return nullptr; // Not found
    }
};
