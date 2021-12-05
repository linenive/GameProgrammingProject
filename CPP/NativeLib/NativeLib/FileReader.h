#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <istream>

using namespace std;

static vector<string> ReadCsvRow(istream& file, char delimiter) {
    stringstream ss;
    bool inquotes = false;
    vector<string> row;//relying on RVO

    while (file.good()) {
        char c = file.get();
        if (!inquotes && c == '"') {
            inquotes = true;
        }
        else if (inquotes && c == '"') {
            if (file.peek() == '"') {
                ss << (char)file.get();
            }
            else {
                inquotes = false;
            }
        }
        else if (!inquotes && c == delimiter) {
            row.push_back(ss.str());
            ss.str("");
        }
        else if (!inquotes && (c == '\r' || c == '\n')) {
            if (file.peek() == '\n') { file.get(); }
            row.push_back(ss.str());
            return row;
        }
        else {
            ss << c;
        }
    }
}
