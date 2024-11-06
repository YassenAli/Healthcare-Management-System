#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileManager {
public:
    fstream openFile(const string &filePath, ios::openmode mode) {
        fstream file(filePath, mode);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filePath << endl;
        }
        return file;
    }

    string readRecordByID(const string &filePath, const string &id) {
        ifstream file(filePath);
        string line;
        while (getline(file, line)) {
            if (line.substr(0, id.length()) == id) {
                return line;
            }
        }
        return "";
    }

    // Add or retrieve record from AVAIL LIST
    void manageAvailList(/* params */) {
        // Logic for managing available space list
    }
};
