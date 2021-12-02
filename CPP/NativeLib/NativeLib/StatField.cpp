#include "StatField.h"

map<eStatFieldType, string> StatField::name_map;
vector<int> StatField::field_order;

void StatField::Init() {
    const string file_path = ".data/stat_name.csv";

    ifstream file(file_path);
    vector<string> row;
    if (file.fail()) {
        cerr << "[StatField]File not found: " << file_path << endl;
        exit(100);
    }

    row = ReadCsvRow(file, ',');
    for (int i = 0; i < row.size(); i++)
        field_order.push_back(stoi(row[i]));

    row = ReadCsvRow(file, ',');
    for (int i = 0; i < row.size(); i++)
        name_map[static_cast<eStatFieldType>(field_order[i])] = row[i];

    file.close();
}