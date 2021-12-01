#pragma once
#pragma execution_character_set("utf-8")
#include "FileReader.h"

using namespace std;

static vector<string> family_name_list = {};
static vector<string> man_name_list = {};
static vector<string> woman_name_list = {};
const string file_path = "data/character_name.csv";

static void LoadNameData() {
	ifstream file(file_path);
    vector<string> row;
	if (file.fail()) {
		cerr << "[NameList]File not found: " << file_path << endl;
		exit(100);
	}

    row = ReadCsvRow(file, ',');
    for (int i = 0; i < row.size(); i++)
        family_name_list.push_back(row[i]);

    row = ReadCsvRow(file, ',');
    for (int i = 0; i < row.size(); i++)
        man_name_list.push_back(row[i]);

    row = ReadCsvRow(file, ',');
    for (int i = 0; i < row.size(); i++)
        woman_name_list.push_back(row[i]);

	file.close();
}
